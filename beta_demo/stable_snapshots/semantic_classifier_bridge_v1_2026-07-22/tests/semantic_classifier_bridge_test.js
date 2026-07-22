const assert = require('assert');
const { spawn } = require('child_process');
const readline = require('readline');
const path = require('path');

const VALID_STATES = new Set([
    'EMPTY',
    'CONFUSED',
    'TIRED',
    'NORMAL'
]);

const VALID_INTENTS = new Set([
    'NONE',
    'ASK_HELP',
    'EMOTION',
    'CHAT'
]);

const VALID_ERRORS = new Set([
    'EMPTY_LINE',
    'INVALID_JSON',
    'REQUEST_NOT_OBJECT',
    'MISSING_REQUEST_ID',
    'INVALID_REQUEST_ID_TYPE',
    'MISSING_USER_TEXT',
    'INVALID_USER_TEXT_TYPE',
    'INTERNAL_ERROR'
]);

const RESPONSE_FIELDS = [
    'request_id',
    'ok',
    'state',
    'intent',
    'danger',
    'self_harm',
    'error'
];

const REQUEST_TIMEOUT_MS = 5000;

let service = null;
let stdoutReader = null;
let closePromise = null;
let bridgeFailure = null;
let rawResponseWaiter = null;
let stdinClosedByTest = false;
let stderrText = '';
let stdoutLineCount = 0;
let successResponseCount = 0;
let errorResponseCount = 0;

const pendingRequests = new Map();
const completedRequestIds = new Set();

function validateResponseShape(response)
{
    assert(
        response !== null
            && typeof response === 'object'
            && !Array.isArray(response),
        'response must be a JSON object'
    );

    assert.deepStrictEqual(
        Object.keys(response).sort(),
        [...RESPONSE_FIELDS].sort(),
        'response fields are not the fixed protocol fields'
    );

    assert.strictEqual(
        typeof response.request_id,
        'string',
        'request_id must be a string'
    );
    assert.strictEqual(
        typeof response.ok,
        'boolean',
        'ok must be a boolean'
    );
    assert.strictEqual(
        typeof response.state,
        'string',
        'state must be a string'
    );
    assert.strictEqual(
        typeof response.intent,
        'string',
        'intent must be a string'
    );
    assert.strictEqual(
        typeof response.danger,
        'boolean',
        'danger must be a boolean'
    );
    assert.strictEqual(
        typeof response.self_harm,
        'boolean',
        'self_harm must be a boolean'
    );
    assert.strictEqual(
        typeof response.error,
        'string',
        'error must be a string'
    );

    assert(
        VALID_STATES.has(response.state),
        `invalid state: ${response.state}`
    );
    assert(
        VALID_INTENTS.has(response.intent),
        `invalid intent: ${response.intent}`
    );

    if (response.ok)
    {
        assert.strictEqual(
            response.error,
            '',
            'successful response error must be empty'
        );
        return;
    }

    assert.strictEqual(response.state, 'EMPTY');
    assert.strictEqual(response.intent, 'NONE');
    assert.strictEqual(response.danger, false);
    assert.strictEqual(response.self_harm, false);
    assert(
        VALID_ERRORS.has(response.error),
        `invalid error code: ${response.error}`
    );
}

function validateExpectedResponse(response, expected)
{
    validateResponseShape(response);

    for (const [field, expectedValue] of Object.entries(expected))
    {
        assert.deepStrictEqual(
            response[field],
            expectedValue,
            `unexpected ${field} for request_id=${response.request_id}`
        );
    }
}

function failBridge(error)
{
    const failure = error instanceof Error
        ? error
        : new Error(String(error));

    if (bridgeFailure === null)
    {
        bridgeFailure = failure;
    }

    for (const pending of pendingRequests.values())
    {
        clearTimeout(pending.timer);
        pending.reject(bridgeFailure);
    }

    pendingRequests.clear();

    if (rawResponseWaiter !== null)
    {
        clearTimeout(rawResponseWaiter.timer);
        rawResponseWaiter.reject(bridgeFailure);
        rawResponseWaiter = null;
    }
}

function handleResponseLine(line)
{
    stdoutLineCount++;

    let response;

    try
    {
        response = JSON.parse(line);
        validateResponseShape(response);
    }
    catch (error)
    {
        failBridge(
            new Error(
                `stdout line ${stdoutLineCount} is invalid JSONL: `
                    + `${line}\n${error.message}`
            )
        );
        return;
    }

    try
    {
        if (rawResponseWaiter !== null)
        {
            const waiter = rawResponseWaiter;
            rawResponseWaiter = null;
            clearTimeout(waiter.timer);
            validateExpectedResponse(response, waiter.expected);
            errorResponseCount++;
            waiter.resolve(response);
            return;
        }

        if (completedRequestIds.has(response.request_id))
        {
            throw new Error(
                `duplicate response request_id: ${response.request_id}`
            );
        }

        const pending = pendingRequests.get(response.request_id);

        if (pending === undefined)
        {
            throw new Error(
                `unknown response request_id: ${response.request_id}`
            );
        }

        pendingRequests.delete(response.request_id);
        clearTimeout(pending.timer);
        validateExpectedResponse(response, pending.expected);
        completedRequestIds.add(response.request_id);

        if (response.ok)
        {
            successResponseCount++;
        }
        else
        {
            errorResponseCount++;
        }

        pending.resolve(response);
    }
    catch (error)
    {
        failBridge(error);
    }
}

function startClassifierService(executablePath)
{
    const resolvedExecutablePath = path.resolve(executablePath);

    service = spawn(
        resolvedExecutablePath,
        [],
        {
            stdio: ['pipe', 'pipe', 'pipe'],
            windowsHide: true
        }
    );

    service.stdin.setDefaultEncoding('utf8');
    service.stderr.setEncoding('utf8');

    stdoutReader = readline.createInterface({
        input: service.stdout,
        crlfDelay: Infinity
    });

    stdoutReader.on('line', handleResponseLine);

    service.stderr.on('data', (chunk) =>
    {
        stderrText += chunk;
    });

    service.on('error', (error) =>
    {
        failBridge(
            new Error(`failed to start C++ service: ${error.message}`)
        );
    });

    service.stdin.on('error', (error) =>
    {
        if (!stdinClosedByTest)
        {
            failBridge(
                new Error(`C++ service stdin error: ${error.message}`)
            );
        }
    });

    closePromise = new Promise((resolve) =>
    {
        service.once('close', (code, signal) =>
        {
            if (!stdinClosedByTest)
            {
                failBridge(
                    new Error(
                        `C++ service exited before stdin EOF: `
                            + `code=${code}, signal=${signal}`
                    )
                );
            }

            if (pendingRequests.size !== 0)
            {
                failBridge(
                    new Error(
                        `C++ service closed with `
                            + `${pendingRequests.size} pending requests`
                    )
                );
            }

            if (rawResponseWaiter !== null)
            {
                failBridge(
                    new Error(
                        'C++ service closed while waiting for an error response'
                    )
                );
            }

            resolve({ code, signal });
        });
    });
}

function waitForRequest(requestId, expected)
{
    assert.strictEqual(
        typeof requestId,
        'string',
        'test request_id must be a string'
    );
    assert(
        !pendingRequests.has(requestId),
        `duplicate pending request_id: ${requestId}`
    );
    assert(
        !completedRequestIds.has(requestId),
        `request_id already completed: ${requestId}`
    );

    return new Promise((resolve, reject) =>
    {
        const timer = setTimeout(() =>
        {
            failBridge(
                new Error(`request timed out: ${requestId}`)
            );
        }, REQUEST_TIMEOUT_MS);

        pendingRequests.set(
            requestId,
            { resolve, reject, expected, timer }
        );
    });
}

function sendRequest(request, expected)
{
    if (bridgeFailure !== null)
    {
        return Promise.reject(bridgeFailure);
    }

    const responsePromise = waitForRequest(
        request.request_id,
        expected
    );

    try
    {
        service.stdin.write(
            `${JSON.stringify(request)}\n`,
            'utf8'
        );
    }
    catch (error)
    {
        failBridge(error);
    }

    return responsePromise;
}

function sendRawLineAndWait(line, expected)
{
    assert.strictEqual(
        pendingRequests.size,
        0,
        'raw error request cannot overlap normal requests'
    );
    assert.strictEqual(
        rawResponseWaiter,
        null,
        'only one raw error request may be pending'
    );

    if (bridgeFailure !== null)
    {
        return Promise.reject(bridgeFailure);
    }

    const responsePromise = new Promise((resolve, reject) =>
    {
        const timer = setTimeout(() =>
        {
            failBridge(
                new Error(
                    `raw request timed out: ${JSON.stringify(line)}`
                )
            );
        }, REQUEST_TIMEOUT_MS);

        rawResponseWaiter = {
            resolve,
            reject,
            expected,
            timer
        };
    });

    try
    {
        service.stdin.write(`${line}\n`, 'utf8');
    }
    catch (error)
    {
        failBridge(error);
    }

    return responsePromise;
}

function waitForServiceClose()
{
    return closePromise;
}

function shutdownService()
{
    if (service !== null && !stdinClosedByTest)
    {
        stdinClosedByTest = true;
        service.stdin.end();
    }
}

async function runBridgeTests()
{
    assert(
        process.argv.length >= 3,
        'usage: node semantic_classifier_bridge_test.js <service_executable_path>'
    );

    startClassifierService(process.argv[2]);

    const successCases = [
        {
            request_id: 'req-001',
            user_text: '',
            state: 'EMPTY',
            intent: 'NONE',
            danger: false,
            self_harm: false
        },
        {
            request_id: 'req-002',
            user_text: '今天天气不错',
            state: 'NORMAL',
            intent: 'CHAT',
            danger: false,
            self_harm: false
        },
        {
            request_id: 'req-003',
            user_text: '我今天很累',
            state: 'TIRED',
            intent: 'EMOTION',
            danger: false,
            self_harm: false
        },
        {
            request_id: 'req-004',
            user_text: '我太累了，不知道怎么办',
            state: 'CONFUSED',
            intent: 'ASK_HELP',
            danger: false,
            self_harm: false
        },
        {
            request_id: 'req-005',
            user_text: '我胸痛，不知道怎么办',
            state: 'CONFUSED',
            intent: 'ASK_HELP',
            danger: true,
            self_harm: false
        },
        {
            request_id: 'req-006',
            user_text: '我不想活了',
            state: 'NORMAL',
            intent: 'CHAT',
            danger: false,
            self_harm: true
        },
        {
            request_id: 'req-007',
            user_text: '我胸痛，而且不想活了',
            state: 'NORMAL',
            intent: 'CHAT',
            danger: true,
            self_harm: true
        },
        {
            request_id: 'req-008',
            user_text: '我很累，想聊京剧',
            state: 'TIRED',
            intent: 'CHAT',
            danger: false,
            self_harm: false
        },
        {
            request_id: '中文请求-009',
            user_text: '今天天气不错',
            state: 'NORMAL',
            intent: 'CHAT',
            danger: false,
            self_harm: false
        },
        {
            request_id: 'req-010',
            user_text: '我想听黄梅戏',
            state: 'NORMAL',
            intent: 'CHAT',
            danger: false,
            self_harm: false
        },
        {
            request_id: 'req-011',
            user_text: '存在多余字段也应正常分类',
            extra: { ignored: true },
            state: 'NORMAL',
            intent: 'CHAT',
            danger: false,
            self_harm: false
        },
        {
            request_id: 'req-012',
            user_text: '这个手机我不会用',
            state: 'CONFUSED',
            intent: 'ASK_HELP',
            danger: false,
            self_harm: false
        },
        {
            request_id: 'req-013',
            user_text: '我胸口很痛，而且喘不上气',
            state: 'NORMAL',
            intent: 'CHAT',
            danger: true,
            self_harm: false
        },
        {
            request_id: 'req-014',
            user_text: '我胸痛，而且很累',
            state: 'TIRED',
            intent: 'EMOTION',
            danger: true,
            self_harm: false
        },
        {
            request_id: 'req-015',
            user_text: '我不想活了，而且很累',
            state: 'TIRED',
            intent: 'EMOTION',
            danger: false,
            self_harm: true
        },
        {
            request_id: 'req-016',
            user_text: '我很累，想说说以前的往事',
            state: 'TIRED',
            intent: 'CHAT',
            danger: false,
            self_harm: false
        },
        {
            request_id: 'req-017',
            user_text: '累计',
            state: 'TIRED',
            intent: 'EMOTION',
            danger: false,
            self_harm: false
        },
        {
            request_id: 'req-018',
            user_text: '不想活跃',
            state: 'NORMAL',
            intent: 'CHAT',
            danger: false,
            self_harm: true
        },
        {
            request_id: 'req-019',
            user_text: '没有胸痛',
            state: 'NORMAL',
            intent: 'CHAT',
            danger: true,
            self_harm: false
        },
        {
            request_id: 'req-020',
            user_text: '想聊豫剧',
            state: 'NORMAL',
            intent: 'CHAT',
            danger: false,
            self_harm: false
        },
        {
            request_id: 'req-021',
            user_text: '我想说说以前的往事',
            state: 'NORMAL',
            intent: 'CHAT',
            danger: false,
            self_harm: false
        },
        {
            request_id: 'req-022',
            user_text: ' \t ',
            state: 'EMPTY',
            intent: 'NONE',
            danger: false,
            self_harm: false
        },
        {
            request_id: 'req-023',
            user_text: '我很孤单，没人陪我说话',
            state: 'NORMAL',
            intent: 'CHAT',
            danger: false,
            self_harm: false
        },
        {
            request_id: 'req-024',
            user_text: '我很累，想聊京剧，而且胸痛',
            state: 'TIRED',
            intent: 'CHAT',
            danger: true,
            self_harm: false
        }
    ];

    const successPromises = [];

    for (const testCase of successCases)
    {
        const request = {
            request_id: testCase.request_id,
            user_text: testCase.user_text
        };

        if (Object.prototype.hasOwnProperty.call(testCase, 'extra'))
        {
            request.extra = testCase.extra;
        }

        successPromises.push(
            sendRequest(
                request,
                {
                    request_id: testCase.request_id,
                    ok: true,
                    state: testCase.state,
                    intent: testCase.intent,
                    danger: testCase.danger,
                    self_harm: testCase.self_harm,
                    error: ''
                }
            )
        );
    }

    await Promise.all(successPromises);

    const validIdErrorCases = [
        {
            request: { request_id: 'err-valid-001' },
            error: 'MISSING_USER_TEXT'
        },
        {
            request: {
                request_id: 'err-valid-002',
                user_text: 123
            },
            error: 'INVALID_USER_TEXT_TYPE'
        },
        {
            request: {
                request_id: 'err-valid-003',
                user_text: null
            },
            error: 'INVALID_USER_TEXT_TYPE'
        },
        {
            request: {
                request_id: 'err-valid-004',
                user_text: []
            },
            error: 'INVALID_USER_TEXT_TYPE'
        }
    ];

    const validIdErrorPromises = [];

    for (const testCase of validIdErrorCases)
    {
        validIdErrorPromises.push(
            sendRequest(
                testCase.request,
                {
                    request_id: testCase.request.request_id,
                    ok: false,
                    state: 'EMPTY',
                    intent: 'NONE',
                    danger: false,
                    self_harm: false,
                    error: testCase.error
                }
            )
        );
    }

    await Promise.all(validIdErrorPromises);

    const rawErrorCases = [
        { line: '{"request_id":', error: 'INVALID_JSON' },
        { line: '', error: 'EMPTY_LINE' },
        { line: ' \t  ', error: 'EMPTY_LINE' },
        { line: '[]', error: 'REQUEST_NOT_OBJECT' },
        { line: '123', error: 'REQUEST_NOT_OBJECT' },
        {
            line: '{"user_text":"missing id"}',
            error: 'MISSING_REQUEST_ID'
        },
        {
            line: '{"request_id":123,"user_text":"bad id"}',
            error: 'INVALID_REQUEST_ID_TYPE'
        },
        {
            line: '{"request_id":null,"user_text":"bad id"}',
            error: 'INVALID_REQUEST_ID_TYPE'
        }
    ];

    for (const testCase of rawErrorCases)
    {
        await sendRawLineAndWait(
            testCase.line,
            {
                request_id: '',
                ok: false,
                state: 'EMPTY',
                intent: 'NONE',
                danger: false,
                self_harm: false,
                error: testCase.error
            }
        );
    }

    shutdownService();

    const closeResult = await waitForServiceClose();

    if (bridgeFailure !== null)
    {
        throw bridgeFailure;
    }

    assert.strictEqual(closeResult.code, 0, 'C++ exit code must be 0');
    assert.strictEqual(closeResult.signal, null, 'C++ must not exit by signal');
    assert.strictEqual(pendingRequests.size, 0);
    assert.strictEqual(rawResponseWaiter, null);
    assert.strictEqual(successResponseCount, successCases.length);
    assert.strictEqual(
        errorResponseCount,
        validIdErrorCases.length + rawErrorCases.length
    );
    assert.strictEqual(
        stdoutLineCount,
        successCases.length
            + validIdErrorCases.length
            + rawErrorCases.length
    );

    console.log('semantic classifier bridge tests passed');
    console.log(`valid requests: ${successCases.length}`);
    console.log(
        `error requests: ${validIdErrorCases.length + rawErrorCases.length}`
    );
    console.log(`continuous requests: ${stdoutLineCount}`);
    console.log('UTF-8 request_id and user_text: passed');
    console.log('danger signal: passed');
    console.log('self_harm signal: passed');
    console.log('danger + self_harm: passed');
    console.log('stdout JSONL only: passed');
    console.log(
        stderrText.length === 0
            ? 'C++ stderr: empty'
            : `C++ stderr:\n${stderrText}`
    );
    console.log(`C++ exit code: ${closeResult.code}`);
}

runBridgeTests().catch(async (error) =>
{
    shutdownService();

    if (closePromise !== null)
    {
        await closePromise.catch(() => {});
    }

    if (stdoutReader !== null)
    {
        stdoutReader.close();
    }

    console.error(error.stack || error.message || String(error));

    if (stderrText.length !== 0)
    {
        console.error(`C++ stderr:\n${stderrText}`);
    }

    process.exitCode = 1;
});
