#include <bits/stdc++.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "speech_input.h"

using namespace std;

void init_console_encoding()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

int main()
{
    init_console_encoding();

    cout << "请输入测试文本：" << flush;

    string user_input;

    if (!read_user_input(user_input))
    {
        cerr << "读取用户输入失败。" << endl;
        return 1;
    }

    cout << "读取结果：" << user_input << endl;

    return 0;
}