#include <bits/stdc++.h>

#include "beta_core.h"
#include "semantic_classifier.h"
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
    const string& processed_input,
    const string& conversation_context)
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
        "请按以下规则判断状态和意图：\n"
        "1. 用户输入为空时，"
        "输出STATE:EMPTY和INTENT:NONE。\n"
        "2. 用户表达不会、不懂、不明白或怎么办等求助时，"
        "输出STATE:CONFUSED和INTENT:ASK_HELP。\n"
        "3. 用户想听或谈论戏曲、京剧、评剧、豫剧、"
        "越剧、黄梅戏或昆曲时，INTENT必须为CHAT。"
        "如果同时出现困、累、疲惫或乏力，"
        "STATE为TIRED，回复先建议安全休息，"
        "再询问用户的戏曲偏好；否则STATE为NORMAL。"
        "如果系统没有实际播放音频，"
        "不得声称已经为用户播放戏曲。\n"
        "4. 用户谈到家庭回忆、往事、以前、过去、"
        "小时候、年轻时、当年或从前时，"
        "INTENT必须为CHAT。"
        "如果同时出现困、累、疲惫或乏力，"
        "STATE为TIRED；否则STATE为NORMAL。"
        "回复应温和倾听并引导用户继续讲述，"
        "不能虚构用户的家庭经历。\n"
        "5. 只有疲惫状态，没有更具体的戏曲或回忆需求时，"
        "输出STATE:TIRED和INTENT:EMOTION。\n"
        "6. 其他普通聊天输出STATE:NORMAL和INTENT:CHAT。\n"
        "普通规则的判断顺序是："
        "空输入、求助、戏曲、家庭回忆、普通疲惫、默认聊天。\n"
        "角色风格不能覆盖安全提醒。\n"
        "你不能进行医疗诊断。"
        "如果输入或图片中出现胸痛、呼吸困难、摔倒、"
        "自伤等危险信息，"
        "ADVICE必须优先建议用户联系家人、"
        "急救服务或专业人员。\n"
        "你必须严格只输出一行，格式如下：\n"
        "STATE:<状态>; INTENT:<意图>; ADVICE:<陪伴回复>\n"
        "STATE只能是EMPTY、CONFUSED、TIRED、NORMAL之一。\n"
        "INTENT只能是NONE、ASK_HELP、EMOTION、CHAT之一。\n"
        "ADVICE中不能出现英文分号。\n"
        "不要输出Markdown、代码块、解释或其他字段。\n"
        "最近对话历史只用于理解指代和承接。"
        "不要机械地把历史状态当成本轮状态，"
        "STATE和INTENT应优先根据当前输入和当前图片判断。\n";

    if (!conversation_context.empty())
    {
        prompt += conversation_context;
        prompt += '\n';
    }

    prompt += "当前老年用户输入：";
    prompt += processed_input;

    return prompt;
}
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

    return "NORMAL";
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

    return "CHAT";
}

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

    SemanticResult semantic_result =
        classify_state_intent(processed_input);

    string state =
        semantic_state_to_string(semantic_result.state);

    string intent =
        semantic_intent_to_string(semantic_result.intent);

    if (semantic_result.state == SemanticState::EMPTY)
    {
        return result_prefix
            + "STATE:" + state
            + "; INTENT:" + intent + "; "
              "ADVICE:您还没有输入内容，"
              "可以告诉我您现在想聊什么，"
              "或者需要什么帮助。";
    }

    if (semantic_result.self_harm)
    {
        return result_prefix
            + "STATE:CONFUSED; "
              "INTENT:ASK_HELP; "
              "ADVICE:听到您这么说，我很担心您的安全。"
              "请先不要独自待着，"
              "马上联系身边可信任的家人、朋友或照护人员，"
              "并联系当地紧急服务或专业人员。"
              "请先远离可能伤害自己的物品，"
              "等待他人陪伴和帮助。";
    }

    if (semantic_result.danger)
    {
        return result_prefix
            + "STATE:CONFUSED; "
              "INTENT:ASK_HELP; "
              "ADVICE:这可能是紧急情况。"
              "请马上联系身边家人或当地急救服务，"
              "不要独自处理。"
              "如果已经摔倒、呼吸困难或明显受伤，"
              "请不要勉强活动，等待他人帮助。";
    }

    if (semantic_result.intent == SemanticIntent::ASK_HELP)
    {
        return result_prefix
            + "STATE:" + state
            + "; INTENT:" + intent + "; "
              "ADVICE:别着急，您可以慢慢告诉我哪里不明白，"
              "我会陪您一起梳理。";
    }

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
        if (semantic_result.state == SemanticState::TIRED)
        {
            return result_prefix
                + "STATE:" + state
                + "; INTENT:" + intent + "; "
                  "ADVICE:听起来您今天有些累，"
                  "可以先坐稳休息一会儿。"
                  "您想听京剧、评剧、豫剧、越剧、"
                  "黄梅戏还是昆曲？";
        }

        return result_prefix
            + "STATE:" + state
            + "; INTENT:" + intent + "; "
              "ADVICE:好呀，我们可以聊聊戏曲。"
              "您想听京剧、评剧、豫剧、越剧、"
              "黄梅戏还是昆曲？";
    }

    if (wants_family_memory)
    {
        if (semantic_result.state == SemanticState::TIRED)
        {
            return result_prefix
                + "STATE:" + state
                + "; INTENT:" + intent + "; "
                  "ADVICE:听起来您现在有些累，"
                  "可以先慢慢休息。"
                  "等舒服一些，再和我说说"
                  "以前与家人相处的难忘往事。";
        }

        return result_prefix
            + "STATE:" + state
            + "; INTENT:" + intent + "; "
              "ADVICE:我愿意听您慢慢讲。"
              "您可以从一件和家人有关、"
              "让您印象最深的往事说起。";
    }

    if (semantic_result.state == SemanticState::TIRED)
    {
        return result_prefix
            + "STATE:" + state
            + "; INTENT:" + intent + "; "
              "ADVICE:您今天可能有些疲惫，"
              "可以先坐稳休息一会儿，"
              "再告诉我现在的感受。";
    }

    return result_prefix
        + "STATE:" + state
        + "; INTENT:" + intent + "; "
          "ADVICE:我在这里陪您。"
          "您可以继续说说那段经历，"
          "或者告诉我现在最想聊的事情。";
}

}

string call_beta_core(
    const string& processed_input,
    const string& image_path,
    VlmClient& vlm_client,
    const string& conversation_context)
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
        build_vlm_prompt(
            processed_input,
            conversation_context
        );

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
