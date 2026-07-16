#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif

#include "logger.h"

using namespace std;

void init_console_encoding()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

string get_time_string()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);

    char buffer[100];

    sprintf(
        buffer,
        "%04d-%02d-%02d %02d:%02d:%02d",
        1900 + ltm->tm_year,
        1 + ltm->tm_mon,
        ltm->tm_mday,
        ltm->tm_hour,
        ltm->tm_min,
        ltm->tm_sec
    );

    return string(buffer);
}

void save_log(
    string user_input,
    string processed_input,
    string core_result,
    string final_response,
    string frame_path,
    bool frame_success)
{
    ofstream fout(
        "logs/beta_log.txt",
        ios::app
    );

    if (!fout.is_open())
    {
        cerr << "警告：日志文件打开失败" << endl;
        return;
    }

    fout << "========== 老年多模态陪伴系统日志 ==========" << endl;
    fout << "时间：" << get_time_string() << endl;
    fout << "原始输入：" << user_input << endl;

    if (frame_success)
    {
        fout << "视频帧状态：成功" << endl;
        fout << "视频帧路径：" << frame_path << endl;
    }
    else
    {
        fout << "视频帧状态：失败" << endl;
        fout << "视频帧路径：无" << endl;
    }

    fout << "预处理后：" << processed_input << endl;
    fout << "核心模块返回：" << core_result << endl;
    fout << "最终输出：" << endl;
    fout << final_response << endl;
    fout << endl;
}