#include <bits/stdc++.h>

#include "beta_core.h"
#include "parser.h"
#include "logger.h"
#include "vlm_client.h"

using namespace std;

int total_count = 0;
int pass_count = 0;

void check_normalize(
    const string& test_name,
    const string& raw_output,
    bool expected_success,
    const string& expected_output)
{
    total_count++;

    string normalized_output = "UNCHANGED";

    bool actual_success =
        normalize_vlm_output(
            raw_output,
            normalized_output
        );

    bool passed =
        actual_success == expected_success;

    if (expected_success)
    {
        passed =
            passed
            && normalized_output == expected_output;
    }

    if (passed)
    {
        pass_count++;

        cout << "[PASS] "
             << test_name
             << '\n';
    }
    else
    {
        cout << "[FAIL] "
             << test_name
             << '\n';

        cout << "  expected_success: "
             << expected_success
             << '\n';

        cout << "  actual_success:   "
             << actual_success
             << '\n';

        cout << "  expected_output:  "
             << expected_output
             << '\n';

        cout << "  actual_output:    "
             << normalized_output
             << '\n';
    }
}

void check_parser(
    const string& test_name,
    const string& core_result,
    const string& expected_output)
{
    total_count++;

    string actual_output =
        parse_result(core_result);

    if (actual_output == expected_output)
    {
        pass_count++;

        cout << "[PASS] "
             << test_name
             << '\n';
    }
    else
    {
        cout << "[FAIL] "
             << test_name
             << '\n';

        cout << "  expected:\n"
             << expected_output
             << '\n';

        cout << "  actual:\n"
             << actual_output
             << '\n';
    }
}

void check_core_result(
    const string& test_name,
    const string& processed_input,
    const string& expected_output,
    VlmClient& vlm_client)
{
    total_count++;

    string actual_output =
        call_beta_core(
            processed_input,
            "",
            vlm_client
        );

    if (actual_output == expected_output)
    {
        pass_count++;

        cout << "[PASS] "
             << test_name
             << '\n';
    }
    else
    {
        cout << "[FAIL] "
             << test_name
             << '\n';

        cout << "  expected:\n"
             << expected_output
             << '\n';

        cout << "  actual:\n"
             << actual_output
             << '\n';
    }
}

void check_prompt(
    const string& test_name,
    const string& processed_input,
    const string& expected_output)
{
    total_count++;

    string actual_output =
        build_vlm_prompt(processed_input);

    if (actual_output == expected_output)
    {
        pass_count++;

        cout << "[PASS] "
             << test_name
             << '\n';
    }
    else
    {
        cout << "[FAIL] "
             << test_name
             << '\n';

        cout << "  expected:\n"
             << expected_output
             << '\n';

        cout << "  actual:\n"
             << actual_output
             << '\n';
    }
}

int main()
{
    init_console_encoding();

    VlmClient vlm_client(
        "",
        "",
        "gpt-5.5"
    );

    check_normalize(
        "normal advice",
        "STATE:NORMAL; INTENT:CHAT; ADVICE:正常建议",
        true,
        "STATE:NORMAL; INTENT:CHAT; ADVICE:正常建议"
    );

    check_normalize(
        "double english colon",
        "STATE:NORMAL; INTENT:CHAT; ADVICE::正常建议",
        true,
        "STATE:NORMAL; INTENT:CHAT; ADVICE:正常建议"
    );

    check_normalize(
        "extra chinese colon",
        "STATE:NORMAL; INTENT:CHAT; ADVICE:：正常建议",
        true,
        "STATE:NORMAL; INTENT:CHAT; ADVICE:正常建议"
    );

    check_normalize(
        "leading spaces",
        "STATE:NORMAL; INTENT:CHAT; ADVICE:   正常建议",
        true,
        "STATE:NORMAL; INTENT:CHAT; ADVICE:正常建议"
    );

    check_normalize(
        "invalid state",
        "STATE:UNKNOWN; INTENT:CHAT; ADVICE:正常建议",
        false,
        ""
    );

    check_normalize(
        "invalid intent",
        "STATE:NORMAL; INTENT:UNKNOWN; ADVICE:正常建议",
        false,
        ""
    );

    check_normalize(
        "empty advice",
        "STATE:NORMAL; INTENT:CHAT; ADVICE:   ",
        false,
        ""
    );

    check_normalize(
        "colon only advice",
        "STATE:NORMAL; INTENT:CHAT; ADVICE::",
        false,
        ""
    );

    check_core_result(
        "mock empty input",
        "",
        "VISION:MISSING; SOURCE:MOCK; "
        "FALLBACK_REASON:摄像头未能提供可用图片。; "
        "STATE:EMPTY; INTENT:NONE; "
        "ADVICE:您还没有输入内容，"
        "可以告诉我您现在想聊什么，"
        "或者需要什么帮助。",
        vlm_client
    );

    check_core_result(
        "mock confused input",
        "我有点不明白该怎么办",
        "VISION:MISSING; SOURCE:MOCK; "
        "FALLBACK_REASON:摄像头未能提供可用图片。; "
        "STATE:CONFUSED; INTENT:ASK_HELP; "
        "ADVICE:别着急，您可以慢慢告诉我哪里不明白，"
        "我会陪您一起梳理。",
        vlm_client
    );

    check_core_result(
        "mock tired input",
        "我今天有点累",
        "VISION:MISSING; SOURCE:MOCK; "
        "FALLBACK_REASON:摄像头未能提供可用图片。; "
        "STATE:TIRED; INTENT:EMOTION; "
        "ADVICE:您今天可能有些疲惫，"
        "可以先坐稳休息一会儿，"
        "再告诉我现在的感受。",
        vlm_client
    );

    check_core_result(
        "mock normal chat",
        "我想聊聊年轻时候的事情",
        "VISION:MISSING; SOURCE:MOCK; "
        "FALLBACK_REASON:摄像头未能提供可用图片。; "
        "STATE:NORMAL; INTENT:CHAT; "
        "ADVICE:我在这里陪您。"
        "您可以继续说说那段经历，"
        "或者告诉我现在最想聊的事情。",
        vlm_client
    );

    string expected_prompt =
        "你是一个基于传统文化IP的老年多模态陪伴助手。"
        "请结合当前图片和老年用户输入，"
        "判断用户的情绪状态和陪伴需求，"
        "并生成一句简短、温和、容易理解的中文陪伴回复。\n"
        "可以根据情况采用以下传统文化角色风格：\n"
        "孙悟空：开朗、勇敢，适合鼓励用户采取安全行动。\n"
        "李白：温和、诗意但必须通俗易懂，适合情绪陪伴和倾听。\n"
        "诸葛亮：沉稳、理性，适合帮助用户梳理问题。\n"
        "角色风格不能覆盖安全提醒。\n"
        "你不能进行医疗诊断。"
        "如果输入或图片中出现胸痛、呼吸困难、摔倒、自伤等危险信息，"
        "ADVICE必须优先建议用户联系家人、急救服务或专业人员。\n"
        "你必须严格只输出一行，格式如下：\n"
        "STATE:<状态>; INTENT:<意图>; ADVICE:<陪伴回复>\n"
        "STATE只能是EMPTY、CONFUSED、TIRED、NORMAL之一。\n"
        "INTENT只能是NONE、ASK_HELP、EMOTION、CHAT之一。\n"
        "ADVICE中不能出现英文分号。\n"
        "不要输出Markdown、代码块、解释或其他字段。\n"
        "老年用户输入：我今天有点孤独";

    check_prompt(
        "aging vlm prompt",
        "我今天有点孤独",
        expected_prompt
    );

    string vlm_expected =
        "视觉输入：UNDERSTOOD\n"
        "回复来源：VLM\n"
        "情绪状态：NORMAL\n"
        "陪伴需求：CHAT\n"
        "陪伴回复：正常建议";

    check_parser(
        "parser vlm result",
        "VISION:UNDERSTOOD; SOURCE:VLM; "
        "STATE:NORMAL; INTENT:CHAT; "
        "ADVICE:正常建议",
        vlm_expected
    );

    string mock_expected =
        "视觉输入：MISSING\n"
        "回复来源：MOCK\n"
        "情绪状态：CONFUSED\n"
        "陪伴需求：ASK_HELP\n"
        "陪伴回复：先别急\n"
        "降级原因：摄像头未能提供可用图片。";

    check_parser(
        "parser mock result",
        "VISION:MISSING; SOURCE:MOCK; "
        "FALLBACK_REASON:摄像头未能提供可用图片。; "
        "STATE:CONFUSED; INTENT:ASK_HELP; "
        "ADVICE:先别急",
        mock_expected
    );

    cout << "\nPassed: "
         << pass_count
         << " / "
         << total_count
         << '\n';

    if (pass_count == total_count)
    {
        cout << "All protocol tests passed.\n";
        return 0;
    }

    cout << "Some protocol tests failed.\n";

    return 1;
}