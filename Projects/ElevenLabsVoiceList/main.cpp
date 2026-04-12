#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "config.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

int main() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, ("xi-api-key: " + apiKey).c_str());
        headers = curl_slist_append(headers, "Accept: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.elevenlabs.io/v1/voices");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            try {
                auto jsonResponse = nlohmann::json::parse(readBuffer);
                std::vector<std::string> voiceInfoList;
                for (const auto& voice : jsonResponse["voices"]) {
                    std::string voiceInfo = "Name: " + voice["name"].get<std::string>() + ", ID: " + voice["voice_id"].get<std::string>() + ", Category: " + voice["category"].get<std::string>();
                    voiceInfoList.push_back(voiceInfo);
                }

                for (size_t i = 0; i < voiceInfoList.size(); ++i) {
                    std::cout << voiceInfoList[i] << std::endl;
                }

            } catch (const nlohmann::json::parse_error& e) {
                std::cerr << "JSON parse error: " << e.what() << std::endl;
            }
        }
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
        return 0;
    }
}
