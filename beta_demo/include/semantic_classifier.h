#ifndef SEMANTIC_CLASSIFIER_H
#define SEMANTIC_CLASSIFIER_H

#include <string>

enum class SemanticState
{
    EMPTY,
    CONFUSED,
    TIRED,
    NORMAL
};

enum class SemanticIntent
{
    NONE,
    ASK_HELP,
    EMOTION,
    CHAT
};

struct SemanticResult
{
    SemanticState state;
    SemanticIntent intent;
    bool danger;
    bool self_harm;
};

SemanticResult classify_state_intent(
    const std::string& user_text
);

#endif
