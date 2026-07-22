#include "semantic_classifier.h"

#include <initializer_list>

using namespace std;

namespace {

bool contains_any_keyword(
    const string& text,
    initializer_list<const char*> keywords)
{
    for (const char* keyword : keywords)
    {
        if (text.find(keyword) != string::npos)
        {
            return true;
        }
    }

    return false;
}

bool is_blank_text(const string& text)
{
    return text.find_first_not_of(" \t\r\n") == string::npos;
}

}

SemanticResult classify_state_intent(
    const string& user_text)
{
    SemanticResult result;

    result.danger = contains_any_keyword(
        user_text,
        {
            "胸痛", "胸口疼", "呼吸困难", "喘不上气",
            "摔倒", "跌倒", "晕倒", "大量出血"
        }
    );

    result.self_harm = contains_any_keyword(
        user_text,
        {"不想活", "轻生", "自伤", "自杀"}
    );

    if (is_blank_text(user_text))
    {
        result.state = SemanticState::EMPTY;
        result.intent = SemanticIntent::NONE;
        return result;
    }

    bool asks_for_help = contains_any_keyword(
        user_text,
        {"不会", "不懂", "没听懂", "不明白", "怎么办"}
    );

    bool is_tired = contains_any_keyword(
        user_text,
        {"困", "累", "疲惫", "乏力"}
    );

    bool wants_opera = contains_any_keyword(
        user_text,
        {
            "戏曲", "京剧", "评剧", "豫剧",
            "越剧", "黄梅戏", "昆曲"
        }
    );

    bool wants_family_memory = contains_any_keyword(
        user_text,
        {
            "回忆", "往事", "以前", "过去",
            "小时候", "年轻时", "当年", "从前"
        }
    );

    if (asks_for_help)
    {
        result.state = SemanticState::CONFUSED;
        result.intent = SemanticIntent::ASK_HELP;
        return result;
    }

    if (wants_opera || wants_family_memory)
    {
        if (is_tired)
        {
            result.state = SemanticState::TIRED;
        }
        else
        {
            result.state = SemanticState::NORMAL;
        }

        result.intent = SemanticIntent::CHAT;
        return result;
    }

    if (is_tired)
    {
        result.state = SemanticState::TIRED;
        result.intent = SemanticIntent::EMOTION;
        return result;
    }

    result.state = SemanticState::NORMAL;
    result.intent = SemanticIntent::CHAT;

    return result;
}
