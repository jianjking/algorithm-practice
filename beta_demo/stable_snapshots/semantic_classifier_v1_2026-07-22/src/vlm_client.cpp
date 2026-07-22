#include "vlm_client.h"

#include <fstream>
#include <string>
#include <vector>

#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

namespace {

const string BASE64_TABLE =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

size_t write_callback(char* ptr,
                      size_t size,
                      size_t nmemb,
                      void* userdata) {
    size_t total_size = size * nmemb;

    string* response =
        static_cast<string*>(userdata);

    response->append(ptr, total_size);

    return total_size;
}

bool read_binary_file(const string& file_path,
                      vector<unsigned char>& data,
                      string& error_message) {
    data.clear();
    error_message.clear();

    ifstream file(
        file_path,
        ios::binary | ios::ate
    );

    if (!file.is_open()) {
        error_message =
            "Cannot open image file: " + file_path;

        return false;
    }

    streamoff file_size = file.tellg();

    if (file_size <= 0) {
        error_message =
            "Image file is empty or its size cannot be read.";

        return false;
    }

    data.resize(
        static_cast<size_t>(file_size)
    );

    file.seekg(0, ios::beg);

    if (!file.read(
            reinterpret_cast<char*>(data.data()),
            static_cast<streamsize>(file_size))) {

        data.clear();

        error_message =
            "Failed to read the complete image file.";

        return false;
    }

    return true;
}

string base64_encode(
    const vector<unsigned char>& data) {

    string encoded;
    size_t i = 0;

    while (i + 2 < data.size()) {
        unsigned int value =
            (static_cast<unsigned int>(data[i]) << 16)
            | (static_cast<unsigned int>(
                   data[i + 1]) << 8)
            | static_cast<unsigned int>(
                  data[i + 2]);

        encoded +=
            BASE64_TABLE[(value >> 18) & 0x3F];

        encoded +=
            BASE64_TABLE[(value >> 12) & 0x3F];

        encoded +=
            BASE64_TABLE[(value >> 6) & 0x3F];

        encoded +=
            BASE64_TABLE[value & 0x3F];

        i += 3;
    }

    size_t remaining = data.size() - i;

    if (remaining == 1) {
        unsigned int value =
            static_cast<unsigned int>(data[i])
            << 16;

        encoded +=
            BASE64_TABLE[(value >> 18) & 0x3F];

        encoded +=
            BASE64_TABLE[(value >> 12) & 0x3F];

        encoded += '=';
        encoded += '=';
    }

    if (remaining == 2) {
        unsigned int value =
            (static_cast<unsigned int>(data[i])
             << 16)
            | (static_cast<unsigned int>(
                   data[i + 1]) << 8);

        encoded +=
            BASE64_TABLE[(value >> 18) & 0x3F];

        encoded +=
            BASE64_TABLE[(value >> 12) & 0x3F];

        encoded +=
            BASE64_TABLE[(value >> 6) & 0x3F];

        encoded += '=';
    }

    return encoded;
}

bool extract_model_answer(const string& response_body,
                          string& answer,
                          string& error_message) {
    answer.clear();
    error_message.clear();

    try {
        json response =
            json::parse(response_body);

        if (!response.contains("choices")) {
            error_message =
                "Response does not contain choices.";

            return false;
        }

        const json& choices =
            response.at("choices");

        if (!choices.is_array()
            || choices.empty()) {

            error_message =
                "choices is not a non-empty array.";

            return false;
        }

        const json& first_choice =
            choices.at(0);

        if (!first_choice.contains("message")) {
            error_message =
                "First choice does not contain message.";

            return false;
        }

        const json& message =
            first_choice.at("message");

        if (!message.is_object()) {
            error_message =
                "message is not an object.";

            return false;
        }

        if (!message.contains("content")) {
            error_message =
                "message does not contain content.";

            return false;
        }

        const json& content =
            message.at("content");

        if (!content.is_string()) {
            error_message =
                "content is not a string.";

            return false;
        }

        answer = content.get<string>();

        if (answer.empty()) {
            error_message =
                "Model answer is empty.";

            return false;
        }

        return true;
    }
    catch (const json::exception& error) {
        error_message =
            string("JSON processing failed: ")
            + error.what();

        return false;
    }
}

}

VlmClient::VlmClient(const string& base_url,
                     const string& api_key,
                     const string& model)
    : base_url(base_url),
      api_key(api_key),
      model(model) {

    if (!this->base_url.empty()
        && this->base_url.back() == '/') {
        this->base_url.pop_back();
    }
}

VlmResult VlmClient::analyze(
    const string& question,
    const string& image_path) {

    VlmResult result;

    if (base_url.empty()) {
        result.error_message =
            "VLM base URL is empty.";

        return result;
    }

    if (api_key.empty()) {
        result.error_message =
            "VLM API Key is empty.";

        return result;
    }

    if (model.empty()) {
        result.error_message =
            "VLM model name is empty.";

        return result;
    }

    if (question.empty()) {
        result.error_message =
            "Question is empty.";

        return result;
    }

    if (image_path.empty()) {
        result.error_message =
            "Image path is empty.";

        return result;
    }

    vector<unsigned char> image_data;
    string helper_error;

    if (!read_binary_file(
            image_path,
            image_data,
            helper_error)) {

        result.error_message = helper_error;
        return result;
    }

    string base64_image =
        base64_encode(image_data);

    if (base64_image.empty()) {
        result.error_message =
            "Base64 encoding produced an empty result.";

        return result;
    }

    string image_data_url =
        "data:image/jpeg;base64,"
        + base64_image;

    string request_body;

    try {
        json text_part;
        text_part["type"] = "text";
        text_part["text"] = question;

        json image_part;
        image_part["type"] = "image_url";
        image_part["image_url"]["url"] =
            image_data_url;

        json content = json::array();
        content.push_back(text_part);
        content.push_back(image_part);

        json message;
        message["role"] = "user";
        message["content"] = content;

        json request;
        request["model"] = model;
        request["messages"] = json::array();
        request["messages"].push_back(message);

        request_body = request.dump();
    }
    catch (const json::exception& error) {
        result.error_message =
            string("Failed to build request JSON: ")
            + error.what();

        return result;
    }

    CURLcode global_result =
        curl_global_init(CURL_GLOBAL_DEFAULT);

    if (global_result != CURLE_OK) {
        result.error_message =
            string("curl_global_init failed: ")
            + curl_easy_strerror(global_result);

        return result;
    }

    CURL* curl = curl_easy_init();

    if (curl == nullptr) {
        result.error_message =
            "curl_easy_init failed.";

        curl_global_cleanup();
        return result;
    }

    string authorization =
        "Authorization: Bearer " + api_key;

    curl_slist* headers = nullptr;
    curl_slist* new_headers = nullptr;

    new_headers = curl_slist_append(
        headers,
        "Content-Type: application/json"
    );

    if (new_headers == nullptr) {
        result.error_message =
            "Failed to create Content-Type header.";

        curl_easy_cleanup(curl);
        curl_global_cleanup();

        return result;
    }

    headers = new_headers;

    new_headers = curl_slist_append(
        headers,
        authorization.c_str()
    );

    if (new_headers == nullptr) {
        result.error_message =
            "Failed to create Authorization header.";

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        curl_global_cleanup();

        return result;
    }

    headers = new_headers;

    string request_url =
        base_url + "/v1/chat/completions";

    string response_body;

    curl_easy_setopt(
        curl,
        CURLOPT_URL,
        request_url.c_str()
    );

    curl_easy_setopt(
        curl,
        CURLOPT_HTTPHEADER,
        headers
    );

    curl_easy_setopt(
        curl,
        CURLOPT_POST,
        1L
    );

    curl_easy_setopt(
        curl,
        CURLOPT_POSTFIELDS,
        request_body.c_str()
    );

    curl_easy_setopt(
        curl,
        CURLOPT_POSTFIELDSIZE,
        static_cast<long>(
            request_body.size()
        )
    );

    curl_easy_setopt(
        curl,
        CURLOPT_WRITEFUNCTION,
        write_callback
    );

    curl_easy_setopt(
        curl,
        CURLOPT_WRITEDATA,
        &response_body
    );

    curl_easy_setopt(
        curl,
        CURLOPT_CONNECTTIMEOUT,
        10L
    );

    curl_easy_setopt(
        curl,
        CURLOPT_TIMEOUT,
        60L
    );

    CURLcode curl_result =
        curl_easy_perform(curl);

    long http_status = 0;

    curl_easy_getinfo(
        curl,
        CURLINFO_RESPONSE_CODE,
        &http_status
    );

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    if (curl_result != CURLE_OK) {
        result.error_message =
            string("VLM request failed: ")
            + curl_easy_strerror(curl_result);

        return result;
    }

    if (http_status < 200
        || http_status >= 300) {

        result.error_message =
            "VLM returned HTTP status "
            + to_string(http_status)
            + ".";

        return result;
    }

    string model_answer;

    if (!extract_model_answer(
            response_body,
            model_answer,
            helper_error)) {

        result.error_message = helper_error;
        return result;
    }

    result.success = true;
    result.content = model_answer;
    result.error_message.clear();

    return result;
}