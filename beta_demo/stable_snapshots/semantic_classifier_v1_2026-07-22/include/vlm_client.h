#ifndef VLM_CLIENT_H
#define VLM_CLIENT_H

#include <string>

struct VlmResult {
    bool success = false;
    std::string content;
    std::string error_message;
};

class VlmClient {
private:
    std::string base_url;
    std::string api_key;
    std::string model;

public:
    VlmClient(const std::string& base_url,
              const std::string& api_key,
              const std::string& model);

    VlmResult analyze(const std::string& question,
                      const std::string& image_path);
};

#endif