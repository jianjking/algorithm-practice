#include <bits/stdc++.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "speech_output.h"

using namespace std;

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    int passed = 0;
    int total = 0;

    total++;

    if (output_companion_reply(
            "视觉输入：FAILED\n"
            "回复来源：MOCK\n"
            "情绪状态：NORMAL\n"
            "陪伴需求：CHAT\n"
            "陪伴回复：测试回复：我在这里陪您慢慢聊。",
            "测试回复：我在这里陪您慢慢聊。"))
    {
        passed++;
    }
    else
    {
        cerr << "正常回复输出测试失败。" << endl;
    }

    total++;

    if (!output_companion_reply(""))
    {
        passed++;
    }
    else
    {
        cerr << "空回复拒绝测试失败。" << endl;
    }

    cout << "测试结果："
         << passed
         << " / "
         << total
         << endl;

    return passed == total ? 0 : 1;
}