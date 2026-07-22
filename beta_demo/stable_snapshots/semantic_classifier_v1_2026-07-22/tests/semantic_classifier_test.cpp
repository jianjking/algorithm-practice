#include <bits/stdc++.h>

#include "semantic_classifier.h"

using namespace std;

int total_count = 0;
int pass_count = 0;
int known_limitation_count = 0;
int known_limitation_match_count = 0;

string state_to_string(SemanticState state)
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

    return "UNKNOWN";
}

string intent_to_string(SemanticIntent intent)
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

    return "UNKNOWN";
}

bool same_result(
    const SemanticResult& left,
    const SemanticResult& right)
{
    return left.state == right.state
        && left.intent == right.intent
        && left.danger == right.danger
        && left.self_harm == right.self_harm;
}

void print_result(
    const string& label,
    const SemanticResult& result)
{
    cout << "  " << label
         << ": STATE=" << state_to_string(result.state)
         << ", INTENT=" << intent_to_string(result.intent)
         << ", danger=" << boolalpha << result.danger
         << ", self_harm=" << result.self_harm
         << '\n';
}

void check_result(
    const string& test_name,
    const string& user_text,
    const SemanticResult& expected)
{
    total_count++;

    SemanticResult actual = classify_state_intent(user_text);

    if (same_result(actual, expected))
    {
        pass_count++;
        cout << "[PASS] " << test_name << '\n';
        print_result("actual", actual);
        return;
    }

    cout << "[FAIL] " << test_name << '\n';
    print_result("expected", expected);
    print_result("actual", actual);
}

void check_known_limitation(
    const string& test_name,
    const string& user_text,
    const SemanticResult& expected_current_result)
{
    known_limitation_count++;

    SemanticResult actual = classify_state_intent(user_text);

    if (same_result(actual, expected_current_result))
    {
        known_limitation_match_count++;
        cout << "[KNOWN LIMITATION] " << test_name << '\n';
        print_result("actual", actual);
        return;
    }

    cout << "[FAIL] known limitation changed: "
         << test_name << '\n';
    print_result("expected current result", expected_current_result);
    print_result("actual", actual);
}

void check_deterministic_result(
    const string& test_name,
    const string& user_text)
{
    total_count++;

    SemanticResult expected = classify_state_intent(user_text);
    bool passed = true;

    for (int i = 0; i < 100; i++)
    {
        SemanticResult actual = classify_state_intent(user_text);

        if (!same_result(actual, expected))
        {
            passed = false;
            break;
        }
    }

    if (passed)
    {
        pass_count++;
        cout << "[PASS] " << test_name << '\n';
        print_result("all 100 calls", expected);
        return;
    }

    cout << "[FAIL] " << test_name << '\n';
}

int main()
{
    check_result(
        "empty string",
        "",
        {SemanticState::EMPTY, SemanticIntent::NONE, false, false}
    );

    check_result(
        "ordinary spaces",
        "   ",
        {SemanticState::EMPTY, SemanticIntent::NONE, false, false}
    );

    check_result(
        "tab",
        "\t",
        {SemanticState::EMPTY, SemanticIntent::NONE, false, false}
    );

    check_result(
        "newline",
        "\n",
        {SemanticState::EMPTY, SemanticIntent::NONE, false, false}
    );

    check_result(
        "mixed whitespace",
        " \t\r\n ",
        {SemanticState::EMPTY, SemanticIntent::NONE, false, false}
    );

    check_result(
        "tired",
        "我今天很累",
        {SemanticState::TIRED, SemanticIntent::EMOTION, false, false}
    );

    check_result(
        "help has priority over tired",
        "我太累了，不知道怎么办",
        {SemanticState::CONFUSED, SemanticIntent::ASK_HELP, false, false}
    );

    check_result(
        "cannot use phone",
        "这个手机我不会用",
        {SemanticState::CONFUSED, SemanticIntent::ASK_HELP, false, false}
    );

    check_result(
        "lonely text follows current default rule",
        "我很孤单，没人陪我说话",
        {SemanticState::NORMAL, SemanticIntent::CHAT, false, false}
    );

    check_result(
        "request without current help keyword",
        "请帮我找眼镜",
        {SemanticState::NORMAL, SemanticIntent::CHAT, false, false}
    );

    check_result(
        "physical danger",
        "我胸口很痛，而且喘不上气",
        {SemanticState::NORMAL, SemanticIntent::CHAT, true, false}
    );

    check_result(
        "self-harm signal",
        "我不想活了",
        {SemanticState::NORMAL, SemanticIntent::CHAT, false, true}
    );

    check_result(
        "physical danger and self-harm together",
        "我胸痛，而且不想活了",
        {SemanticState::NORMAL, SemanticIntent::CHAT, true, true}
    );

    check_result(
        "danger remains true with ASK_HELP",
        "我胸痛，不知道怎么办",
        {SemanticState::CONFUSED, SemanticIntent::ASK_HELP, true, false}
    );

    check_result(
        "tired and help",
        "我很疲惫，不明白怎么办",
        {SemanticState::CONFUSED, SemanticIntent::ASK_HELP, false, false}
    );

    check_result(
        "tired and opera",
        "我很累，想聊京剧",
        {SemanticState::TIRED, SemanticIntent::CHAT, false, false}
    );

    check_result(
        "tired and family memory",
        "我很累，想说说以前的往事",
        {SemanticState::TIRED, SemanticIntent::CHAT, false, false}
    );

    check_result(
        "ordinary chat",
        "今天天气不错",
        {SemanticState::NORMAL, SemanticIntent::CHAT, false, false}
    );

    check_deterministic_result(
        "same input is deterministic for 100 calls",
        "我很累，想聊京剧，而且胸痛"
    );

    check_result(
        "danger remains true with EMOTION",
        "我胸痛，而且很累",
        {SemanticState::TIRED, SemanticIntent::EMOTION, true, false}
    );

    check_result(
        "danger remains true with CHAT",
        "我胸痛，想聊京剧",
        {SemanticState::NORMAL, SemanticIntent::CHAT, true, false}
    );

    check_result(
        "self-harm remains true with TIRED",
        "我不想活了，而且很累",
        {SemanticState::TIRED, SemanticIntent::EMOTION, false, true}
    );

    check_result(
        "self-harm remains true with CONFUSED",
        "我不想活了，不知道怎么办",
        {SemanticState::CONFUSED, SemanticIntent::ASK_HELP, false, true}
    );

    check_result(
        "self-harm remains true with NORMAL",
        "我不想活了",
        {SemanticState::NORMAL, SemanticIntent::CHAT, false, true}
    );

    check_known_limitation(
        "累计 matches the tired keyword 累",
        "累计",
        {SemanticState::TIRED, SemanticIntent::EMOTION, false, false}
    );

    check_known_limitation(
        "不想活跃 matches the self-harm substring 不想活",
        "不想活跃",
        {SemanticState::NORMAL, SemanticIntent::CHAT, false, true}
    );

    check_known_limitation(
        "没有胸痛 matches the danger keyword 胸痛",
        "没有胸痛",
        {SemanticState::NORMAL, SemanticIntent::CHAT, true, false}
    );

    cout << "\nFunctional checks passed: "
         << pass_count
         << " / "
         << total_count
         << '\n';

    cout << "Known limitations reproduced: "
         << known_limitation_match_count
         << " / "
         << known_limitation_count
         << '\n';

    if (pass_count == total_count
        && known_limitation_match_count == known_limitation_count)
    {
        cout << "semantic classifier tests passed\n";
        return 0;
    }

    cout << "semantic classifier tests failed\n";
    return 1;
}
