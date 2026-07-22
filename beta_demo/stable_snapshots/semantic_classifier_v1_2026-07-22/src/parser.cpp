#include <bits/stdc++.h>
#include "parser.h"

using namespace std;

string get_field(string text, string field_name)
{
    string key = field_name + ":";

    int pos = text.find(key);

    if (pos == -1)
    {
        return "";
    }

    pos += key.size();

    int end_pos = text.find(";", pos);

    if (end_pos == -1)
    {
        end_pos = text.size();
    }

    return text.substr(pos, end_pos - pos);
}

string parse_result(string core_result)
{
    string vision = get_field(core_result, "VISION");
    string source = get_field(core_result, "SOURCE");

    string fallback_reason =
        get_field(core_result, "FALLBACK_REASON");

    string state = get_field(core_result, "STATE");
    string intent = get_field(core_result, "INTENT");
    string advice = get_field(core_result, "ADVICE");

    string final_response = "";

    final_response += "视觉输入：" + vision + "\n";
    final_response += "回复来源：" + source + "\n";


    final_response += "情绪状态：" + state + "\n";


    final_response += "陪伴需求：" + intent + "\n";

    final_response += "陪伴回复：" + advice;

    if (!fallback_reason.empty())
    {
        final_response +=
            "\n降级原因：" + fallback_reason;
    }

    return final_response;
}