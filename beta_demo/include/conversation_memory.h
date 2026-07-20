#ifndef CONVERSATION_MEMORY_H
#define CONVERSATION_MEMORY_H

#include <deque>
#include <string>

struct ConversationTurn
{
    std::string user_input;
    std::string companion_reply;
};

void add_conversation_turn(
    std::deque<ConversationTurn>& memory,
    const std::string& user_input,
    const std::string& companion_reply
);

std::string build_conversation_context(
    const std::deque<ConversationTurn>& memory
);

#endif