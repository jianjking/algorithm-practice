#include <bits/stdc++.h>
#include "logger.h"
#include "conversation_memory.h"

using namespace std;

void check_result(
    bool condition,
    const string& test_name,
    int& passed,
    int& total)
{
    total++;

    if (condition)
    {
        passed++;
        cout << "[PASS] " << test_name << endl;
    }
    else
    {
        cout << "[FAIL] " << test_name << endl;
    }
}

int main()
{
    int passed = 0;
    int total = 0;
init_console_encoding();
    deque<ConversationTurn> memory;

    string empty_context =
        build_conversation_context(memory);

    check_result(
        empty_context.empty(),
        "空记忆返回空字符串",
        passed,
        total
    );

    add_conversation_turn(
        memory,
        "我想起年轻时过春节。",
        "那一定是一段很温暖的回忆。"
    );

    check_result(
        memory.size() == 1,
        "加入第一轮后记忆数量为1",
        passed,
        total
    );

    check_result(
        memory[0].user_input
            == "我想起年轻时过春节。",
        "正确保存第一轮用户输入",
        passed,
        total
    );

    check_result(
        memory[0].companion_reply
            == "那一定是一段很温暖的回忆。",
        "正确保存第一轮陪伴回复",
        passed,
        total
    );

    string first_context =
        build_conversation_context(memory);

    check_result(
        first_context.find("我想起年轻时过春节。")
            != string::npos,
        "上下文包含用户输入",
        passed,
        total
    );

    check_result(
        first_context.find("那一定是一段很温暖的回忆。")
            != string::npos,
        "上下文包含陪伴回复",
        passed,
        total
    );

    add_conversation_turn(
        memory,
        "我们一家人会一起贴春联。",
        "一家人一起贴春联确实很有年味。"
    );

    add_conversation_turn(
        memory,
        "我还记得年夜饭特别热闹。",
        "听起来那顿年夜饭让您印象很深。"
    );

    add_conversation_turn(
        memory,
        "我最喜欢母亲做的饺子。",
        "母亲做的饺子一定承载着很多回忆。"
    );

    check_result(
        memory.size() == 3,
        "超过三轮后仍只保存三轮",
        passed,
        total
    );

    check_result(
        memory.front().user_input
            == "我们一家人会一起贴春联。",
        "超过三轮后删除最早一轮",
        passed,
        total
    );

    string final_context =
        build_conversation_context(memory);

    check_result(
        final_context.find("我想起年轻时过春节。")
            == string::npos,
        "整理后的上下文不再包含已删除轮次",
        passed,
        total
    );

    check_result(
        final_context.find("我最喜欢母亲做的饺子。")
            != string::npos,
        "整理后的上下文包含最新一轮",
        passed,
        total
    );

    cout << endl;
    cout << "conversation_memory_test: "
         << passed
         << " / "
         << total
         << endl;

    return passed == total ? 0 : 1;
}