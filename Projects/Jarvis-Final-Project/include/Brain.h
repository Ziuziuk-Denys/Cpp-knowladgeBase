#pragma once
#include <curl/curl.h>
#include <curl/easy.h>
#include <nlohmann/json_fwd.hpp>
#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "Config.h"

class Brain {
public:
    std::string gemini_response;
    using json = nlohmann::json;

    static size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
        size_t totalSize = size * nmemb;
        output->append((char*)contents, totalSize);
        return totalSize;
    }

    void askGemini(const std::string& text) {
        CURL* curl = curl_easy_init();
        if (!curl) return;

        std::string model = "gemini-2.5-flash";
        std::string response_string;
        std::string url = "https://generativelanguage.googleapis.com/v1beta/models/" + model + ":generateContent?key=" + std::string(GEMINI_API_KEY);

        json requestBody = {
            {"contents", {{
                {"parts", {{
                    {"text", "You are Jarvis. Answer concisely, maintaining full context. Act as a helpful human-like assistant." + text}
                }}}
            }}}
        };
        std::string payloadStr = requestBody.dump();

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payloadStr.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        try {
            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "curl failed: " << curl_easy_strerror(res) << std::endl;
            } else {
                json data = json::parse(response_string);
                if (data.contains("candidates")) {
                    std::string answer = data["candidates"][0]["content"]["parts"][0]["text"].get<std::string>();
                    std::cout << "Answer: " << answer << std::endl;
                    gemini_response = answer;
                } else {
                    std::cerr << "Unexpected JSON: " << data.dump() << std::endl;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
};
