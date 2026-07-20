#include "conversation_memory.h"

#include <sstream>

using namespace std;

namespace {

const size_t MAX_MEMORY_TURNS = 3;

}

void add_conversation_turn(
    deque<ConversationTurn>& memory,
    const string& user_input,
    const string& companion_reply)
{
    ConversationTurn turn;

    turn.user_input = user_input;
    turn.companion_reply = companion_reply;

    memory.push_back(turn);

    while (memory.size() > MAX_MEMORY_TURNS)
    {
        memory.pop_front();
    }
}

string build_conversation_context(
    const deque<ConversationTurn>& memory)
{
    if (memory.empty())
    {
        return "";
    }

    stringstream context_builder;

    context_builder
        << "最近对话历史：\n";

    for (size_t i = 0; i < memory.size(); i++)
    {
        context_builder
            << "第"
            << i + 1
            << "轮用户："
            << memory[i].user_input
            << "\n";

        context_builder
            << "第"
            << i + 1
            << "轮助手："
            << memory[i].companion_reply
            << "\n";
    }

    return context_builder.str();
}