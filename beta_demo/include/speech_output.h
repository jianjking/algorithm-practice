#ifndef SPEECH_OUTPUT_H
#define SPEECH_OUTPUT_H

#include <string>

bool output_companion_reply(
    const std::string& reply);

bool output_companion_reply(
    const std::string& display_reply,
    const std::string& spoken_reply);

#endif