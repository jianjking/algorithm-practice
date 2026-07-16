#include <bits/stdc++.h>
#include <filesystem>

#include "logger.h"

using namespace std;

namespace fs = std::filesystem;

int total_count = 0;
int pass_count = 0;

void check_true(
    const string& test_name,
    bool condition)
{
    total_count++;

    if (condition)
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
    }
}

void check_contains(
    const string& test_name,
    const string& text,
    const string& expected_part)
{
    total_count++;

    if (text.find(expected_part)
        != string::npos)
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

        cout << "  expected part:\n"
             << expected_part
             << '\n';
    }
}

string read_text_file(
    const fs::path& file_path)
{
    ifstream fin(
        file_path,
        ios::binary
    );

    if (!fin.is_open())
    {
        return "";
    }

    stringstream content_builder;
    content_builder << fin.rdbuf();

    return content_builder.str();
}

int main()
{
    init_console_encoding();

    fs::path project_directory =
        fs::current_path();

    fs::path success_workspace =
        project_directory
        / "tests"
        / "logger_test_workspace";

    fs::path failure_workspace =
        project_directory
        / "tests"
        / "logger_failure_workspace";

    error_code error;

    fs::remove_all(
        success_workspace,
        error
    );

    error.clear();

    fs::remove_all(
        failure_workspace,
        error
    );

    error.clear();

    fs::create_directories(
        success_workspace / "logs",
        error
    );

    if (error)
    {
        cerr << "无法创建日志测试目录："
             << error.message()
             << endl;

        return 1;
    }

    fs::create_directories(
        failure_workspace,
        error
    );

    if (error)
    {
        cerr << "无法创建日志失败测试目录："
             << error.message()
             << endl;

        return 1;
    }

    fs::current_path(
        success_workspace,
        error
    );

    if (error)
    {
        cerr << "无法进入日志测试目录："
             << error.message()
             << endl;

        return 1;
    }

    save_log(
        "测试成功输入",
        "测试成功输入",
        "VISION:UNDERSTOOD; SOURCE:VLM; "
        "STATE:NORMAL; INTENT:CHAT; "
        "ADVICE:测试陪伴回复",
        "视觉输入：UNDERSTOOD\n"
        "回复来源：VLM\n"
        "情绪状态：NORMAL\n"
        "陪伴需求：CHAT\n"
        "陪伴回复：测试陪伴回复",
        "frames/test_001.jpg",
        true
    );

    save_log(
        "测试失败输入",
        "测试失败输入",
        "VISION:MISSING; SOURCE:MOCK; "
        "FALLBACK_REASON:测试摄像头失败; "
        "STATE:TIRED; INTENT:EMOTION; "
        "ADVICE:测试文字降级回复",
        "视觉输入：MISSING\n"
        "回复来源：MOCK\n"
        "情绪状态：TIRED\n"
        "陪伴需求：EMOTION\n"
        "陪伴回复：测试文字降级回复\n"
        "降级原因：测试摄像头失败",
        "frames/test_002.jpg",
        false
    );

    fs::current_path(
        project_directory,
        error
    );

    if (error)
    {
        cerr << "无法返回项目目录："
             << error.message()
             << endl;

        return 1;
    }

    fs::path log_path =
        success_workspace
        / "logs"
        / "beta_log.txt";

    check_true(
        "log file created",
        fs::exists(log_path)
    );

    string log_content =
        read_text_file(log_path);

    check_contains(
        "aging companion log title",
        log_content,
        "========== 老年多模态陪伴系统日志 =========="
    );

    check_contains(
        "success raw input",
        log_content,
        "原始输入：测试成功输入"
    );

    check_contains(
        "success frame status",
        log_content,
        "视频帧状态：成功"
    );

    check_contains(
        "success frame path",
        log_content,
        "视频帧路径：frames/test_001.jpg"
    );

    check_contains(
        "failure raw input",
        log_content,
        "原始输入：测试失败输入"
    );

    check_contains(
        "failure frame status",
        log_content,
        "视频帧状态：失败"
    );

    check_contains(
        "failure frame path",
        log_content,
        "视频帧路径：无"
    );

    check_contains(
        "core result recorded",
        log_content,
        "SOURCE:MOCK"
    );

    check_contains(
        "final response recorded",
        log_content,
        "陪伴回复：测试文字降级回复"
    );

    ostringstream captured_error;

    streambuf* original_error_buffer =
        cerr.rdbuf(
            captured_error.rdbuf()
        );

    fs::current_path(
        failure_workspace,
        error
    );

    if (!error)
    {
        save_log(
            "无法写入测试",
            "无法写入测试",
            "STATE:NORMAL; INTENT:CHAT; "
            "ADVICE:不会真正写入",
            "陪伴回复：不会真正写入",
            "frames/test_003.jpg",
            false
        );
    }

    error.clear();

    fs::current_path(
        project_directory,
        error
    );

    cerr.rdbuf(
        original_error_buffer
    );

    if (error)
    {
        cerr << "日志失败测试后无法返回项目目录："
             << error.message()
             << endl;

        return 1;
    }

    check_contains(
        "log open failure warning",
        captured_error.str(),
        "警告：日志文件打开失败"
    );

    error.clear();

    fs::remove_all(
        success_workspace,
        error
    );

    error.clear();

    fs::remove_all(
        failure_workspace,
        error
    );

    cout << "\nPassed: "
         << pass_count
         << " / "
         << total_count
         << '\n';

    if (pass_count == total_count)
    {
        cout << "All logger tests passed."
             << '\n';

        return 0;
    }

    cout << "Some logger tests failed."
         << '\n';

    return 1;
}