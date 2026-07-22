#include <bits/stdc++.h>
#include <nlohmann/json.hpp>

#include "semantic_classifier.h"

using namespace std;
using json = nlohmann::json;

namespace {

string semantic_state_to_string(SemanticState state)
{
    switch (state)
    {
        case SemanticState::EMPTY:
            return "EMPTY";
        case SemanticState::CONFUSED:
            return "CONFUSED";
        case SemanticState::TIRED:
            return "TIRED";
        case SemanticState::NORMAL:
            return "NORMAL";
    }

    throw runtime_error("unknown semantic state");
}

string semantic_intent_to_string(SemanticIntent intent)
{
    switch (intent)
    {
        case SemanticIntent::NONE:
            return "NONE";
        case SemanticIntent::ASK_HELP:
            return "ASK_HELP";
        case SemanticIntent::EMOTION:
            return "EMOTION";
        case SemanticIntent::CHAT:
            return "CHAT";
    }

    throw runtime_error("unknown semantic intent");
}

json make_error_response(
    const string& request_id,
    const string& error)
{
    return {
        {"request_id", request_id},
        {"ok", false},
        {"state", "EMPTY"},
        {"intent", "NONE"},
        {"danger", false},
        {"self_harm", false},
        {"error", error}
    };
}

json make_success_response(
    const string& request_id,
    const SemanticResult& result)
{
    return {
        {"request_id", request_id},
        {"ok", true},
        {"state", semantic_state_to_string(result.state)},
        {"intent", semantic_intent_to_string(result.intent)},
        {"danger", result.danger},
        {"self_harm", result.self_harm},
        {"error", ""}
    };
}

json process_request_line(const string& line)
{
    if (line.find_first_not_of(" \t\r\n") == string::npos)
    {
        return make_error_response("", "EMPTY_LINE");
    }

    json request;

    try
    {
        request = json::parse(line);
    }
    catch (const json::parse_error&)
    {
        return make_error_response("", "INVALID_JSON");
    }
    catch (const exception&)
    {
        return make_error_response("", "INTERNAL_ERROR");
    }

    if (!request.is_object())
    {
        return make_error_response("", "REQUEST_NOT_OBJECT");
    }

    if (!request.contains("request_id"))
    {
        return make_error_response("", "MISSING_REQUEST_ID");
    }

    if (!request["request_id"].is_string())
    {
        return make_error_response("", "INVALID_REQUEST_ID_TYPE");
    }

    string request_id;

    try
    {
        request_id = request["request_id"].get<string>();

        if (!request.contains("user_text"))
        {
            return make_error_response(
                request_id,
                "MISSING_USER_TEXT"
            );
        }

        if (!request["user_text"].is_string())
        {
            return make_error_response(
                request_id,
                "INVALID_USER_TEXT_TYPE"
            );
        }

        const string user_text =
            request["user_text"].get<string>();

        const SemanticResult result =
            classify_state_intent(user_text);

        return make_success_response(
            request_id,
            result
        );
    }
    catch (const exception&)
    {
        return make_error_response(
            request_id,
            "INTERNAL_ERROR"
        );
    }
}

}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;

    while (getline(cin, line))
    {
        json response;

        try
        {
            response = process_request_line(line);
        }
        catch (const exception&)
        {
            response = make_error_response(
                "",
                "INTERNAL_ERROR"
            );
        }

        cout << response.dump()
             << '\n'
             << flush;
    }

    return 0;
}
