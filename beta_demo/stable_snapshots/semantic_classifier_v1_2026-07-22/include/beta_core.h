#ifndef BETA_CORE_H
#define BETA_CORE_H

#include <string>

class VlmClient;

bool normalize_vlm_output(
    const std::string& raw_output,
    std::string& normalized_output
);

std::string build_vlm_prompt(
    const std::string& processed_input,
    const std::string& conversation_context = ""
);

std::string call_beta_core(
    const std::string& processed_input,
    const std::string& image_path,
    VlmClient& vlm_client,
    const std::string& conversation_context = ""
);

#endif