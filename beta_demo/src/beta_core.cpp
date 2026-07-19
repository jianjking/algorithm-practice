#include <bits/stdc++.h>

#include "beta_core.h"
#include "vlm_client.h"

using namespace std;

namespace {

string trim_text(const string& text)
{
    size_t first =
        text.find_first_not_of(" \t\r\n");

    if (first == string::npos)
    {
        return "";
    }

    size_t last =
        text.find_last_not_of(" \t\r\n");

    return text.substr(
        first,
        last - first + 1
    );
}

string extract_vlm_field(
    const string& text,
    const string& field_name)
{
    string key = field_name + ":";

    size_t position = text.find(key);

    if (position == string::npos)
    {
        return "";
    }

    position += key.size();

    size_t end_position =
        text.find(";", position);

    if (end_position == string::npos)
    {
        end_position = text.size();
    }

    return trim_text(
        text.substr(
            position,
            end_position - position
        )
    );
}

string sanitize_field(string text)
{
    text = trim_text(text);

    const string chinese_colon = "：";

    while (true)
    {
        if (!text.empty()
            && text[0] == ':')
        {
            text.erase(0, 1);
            text = trim_text(text);
            continue;
        }

        if (text.rfind(
                chinese_colon,
                0) == 0)
        {
            text.erase(
                0,
                chinese_colon.size()
            );

            text = trim_text(text);
            continue;
        }

        break;
    }

    for (size_t i = 0;
         i < text.size();
         i++)
    {
        if (text[i] == ';')
        {
            text[i] = ',';
        }

        if (text[i] == '\n'
            || text[i] == '\r')
        {
            text[i] = ' ';
        }
    }

    return trim_text(text);
}

bool is_valid_state(const string& state)
{
    return state == "EMPTY"
        || state == "CONFUSED"
        || state == "TIRED"
        || state == "NORMAL";
}

bool is_valid_intent(const string& intent)
{
    return intent == "NONE"
        || intent == "ASK_HELP"
        || intent == "EMOTION"
        || intent == "CHAT";
}

}

bool normalize_vlm_output(
    const string& raw_output,
    string& normalized_output)
{
    string state =
        extract_vlm_field(
            raw_output,
            "STATE"
        );

    string intent =
        extract_vlm_field(
            raw_output,
            "INTENT"
        );

    string advice =
        extract_vlm_field(
            raw_output,
            "ADVICE"
        );

    string sanitized_advice =
        sanitize_field(advice);

    if (!is_valid_state(state))
    {
        return false;
    }

    if (!is_valid_intent(intent))
    {
        return false;
    }

    if (sanitized_advice.empty())
    {
        return false;
    }

    normalized_output =
        "STATE:" + state
        + "; INTENT:" + intent
        + "; ADVICE:"
        + sanitized_advice;

    return true;
}

string build_vlm_prompt(
    const string& processed_input)
{
    string prompt =
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
        "老年用户输入：";

    prompt += processed_input;

    return prompt;
}

namespace {

string build_mock_result(
    const string& processed_input,
    const string& vision_status,
    const string& fallback_reason)
{
    string result_prefix =
        "VISION:" + vision_status
        + "; SOURCE:MOCK; ";

    if (!fallback_reason.empty())
    {
        result_prefix +=
            "FALLBACK_REASON:"
            + sanitize_field(fallback_reason)
            + "; ";
    }

    if (processed_input.empty())
    {
        return result_prefix
            + "STATE:EMPTY; INTENT:NONE; "
              "ADVICE:您还没有输入内容，"
              "可以告诉我您现在想聊什么，"
              "或者需要什么帮助。";
    }

    if (processed_input.find("不会")
            != string::npos
        || processed_input.find("不懂")
            != string::npos
        || processed_input.find("没听懂")
            != string::npos
        || processed_input.find("不明白")
            != string::npos
        || processed_input.find("怎么办")
            != string::npos)
    {
        return result_prefix
            + "STATE:CONFUSED; "
              "INTENT:ASK_HELP; "
              "ADVICE:别着急，您可以慢慢告诉我哪里不明白，"
              "我会陪您一起梳理。";
    }

    bool is_tired =
        processed_input.find("困") != string::npos
        || processed_input.find("累") != string::npos
        || processed_input.find("疲惫") != string::npos
        || processed_input.find("乏力") != string::npos;

    bool wants_opera =
        processed_input.find("戏曲") != string::npos
        || processed_input.find("京剧") != string::npos
        || processed_input.find("评剧") != string::npos
        || processed_input.find("豫剧") != string::npos
        || processed_input.find("越剧") != string::npos
        || processed_input.find("黄梅戏") != string::npos
        || processed_input.find("昆曲") != string::npos;

    bool wants_family_memory =
        processed_input.find("回忆") != string::npos
        || processed_input.find("往事") != string::npos
        || processed_input.find("以前") != string::npos
        || processed_input.find("过去") != string::npos
        || processed_input.find("小时候") != string::npos
        || processed_input.find("年轻时") != string::npos
        || processed_input.find("当年") != string::npos
        || processed_input.find("从前") != string::npos;

    if (wants_opera)
    {
        if (is_tired)
        {
            return result_prefix
                + "STATE:TIRED; "
                  "INTENT:CHAT; "
                  "ADVICE:听起来您今天有些累，"
                  "可以先坐稳休息一会儿。"
                  "您想听京剧、评剧、豫剧、越剧、"
                  "黄梅戏还是昆曲？";
        }

        return result_prefix
            + "STATE:NORMAL; "
              "INTENT:CHAT; "
              "ADVICE:好呀，我们可以聊聊戏曲。"
              "您想听京剧、评剧、豫剧、越剧、"
              "黄梅戏还是昆曲？";
    }

    if (wants_family_memory)
    {
        if (is_tired)
        {
            return result_prefix
                + "STATE:TIRED; "
                  "INTENT:CHAT; "
                  "ADVICE:听起来您现在有些累，"
                  "可以先慢慢休息。"
                  "等舒服一些，再和我说说"
                  "以前与家人相处的难忘往事。";
        }

        return result_prefix
            + "STATE:NORMAL; "
              "INTENT:CHAT; "
              "ADVICE:我愿意听您慢慢讲。"
              "您可以从一件和家人有关、"
              "让您印象最深的往事说起。";
    }

    if (is_tired)
    {
        return result_prefix
            + "STATE:TIRED; "
              "INTENT:EMOTION; "
              "ADVICE:您今天可能有些疲惫，"
              "可以先坐稳休息一会儿，"
              "再告诉我现在的感受。";
    }

    return result_prefix
        + "STATE:NORMAL; INTENT:CHAT; "
          "ADVICE:我在这里陪您。"
          "您可以继续说说那段经历，"
          "或者告诉我现在最想聊的事情。";
}

}

string call_beta_core(
    const string& processed_input,
    const string& image_path,
    VlmClient& vlm_client)
{
    if (image_path.empty())
    {
        return build_mock_result(
            processed_input,
            "MISSING",
            "摄像头未能提供可用图片。"
        );
    }

    string vlm_prompt =
        build_vlm_prompt(processed_input);

    VlmResult vlm_result =
        vlm_client.analyze(
            vlm_prompt,
            image_path
        );

    if (!vlm_result.success)
    {
        return build_mock_result(
            processed_input,
            "FAILED",
            vlm_result.error_message
        );
    }

    string normalized_output;

    if (!normalize_vlm_output(
            vlm_result.content,
            normalized_output))
    {
        return build_mock_result(
            processed_input,
            "FAILED",
            "VLM response format is invalid."
        );
    }

    return
        "VISION:UNDERSTOOD; SOURCE:VLM; "
        + normalized_output;
}