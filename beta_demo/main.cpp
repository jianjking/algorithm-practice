#include <bits/stdc++.h>
#include <cstdlib>
#include "speech_output.h"
#include "beta_core.h"
#include "logger.h"
#include "parser.h"
#include "preprocess.h"
#include "camera_capture.h"
#include "vlm_client.h"
#include "speech_input.h"
using namespace std;

int main()
{
    init_console_encoding();

    cout << "传统文化 IP 老年多模态陪伴系统 - C++ Demo" << endl;
    cout << "输入 exit 退出程序。" << endl;
    cout << endl;

    const char* base_url_env = getenv("VLM_BASE_URL");
    const char* api_key_env = getenv("VLM_API_KEY");

    string base_url =
        base_url_env != nullptr ? base_url_env : "";

    string api_key =
        api_key_env != nullptr ? api_key_env : "";

    if (base_url.empty() || api_key.empty())
    {
        cout << "警告：VLM配置不完整，VLM失败时将使用文字mock降级。"
             << endl;
    }

    VlmClient vlm_client(
        base_url,
        api_key,
        "gpt-5.5"
    );

    int frame_index = 1;

    while (true)
    {
        cout << "请输入您现在想说的话：";

        string user_input;

        if (!read_user_input(user_input))
        {
            break;
        }

        if (user_input == "exit")
        {
            cout << "程序已退出。" << endl;
            break;
        }

        stringstream path_builder;

        path_builder << "frames/frame_"
                     << setw(3)
                     << setfill('0')
                     << frame_index
                     << ".jpg";

        string frame_path = path_builder.str();

        frame_index++;

        bool frame_success =
            capture_frame(frame_path);

        string image_path = "";

        if (frame_success)
        {
            image_path = frame_path;

            cout << "视频帧捕获成功："
                 << frame_path
                 << endl;
        }
        else
        {
            cout << "警告：视频帧捕获失败，将继续处理文字输入。"
                 << endl;
        }

        string processed_input =
            preprocess(user_input);

        string core_result =
            call_beta_core(
                processed_input,
                image_path,
                vlm_client
            );

        string final_response =
    parse_result(core_result);

string companion_reply =
    get_field(core_result, "ADVICE");

cout << endl;
cout << "===== 系统反馈 =====" << endl;

if (!output_companion_reply(
        final_response,
        companion_reply))
{
    cerr << "错误：陪伴回复输出失败。" << endl;
}

        cout << "====================" << endl;
        cout << endl;

        save_log(
            user_input,
            processed_input,
            core_result,
            final_response,
            frame_path,
            frame_success
        );
    }

    return 0;
}