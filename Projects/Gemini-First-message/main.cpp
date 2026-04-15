#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "config.h"

using json = nlohmann::json;

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

int main() {
    std::string model = "gemini-2.5-flash";
    std::string response_string;


    std::string url = "https://generativelanguage.googleapis.com/v1beta/models/" + model + ":generateContent?key=" + GEMINI_API;

    std::string user_request = "";
    std::cout << "Enter your qestion: ";
    std::cin >> user_request;

    CURL *curl = curl_easy_init();
    curl_global_init(CURL_GLOBAL_DEFAULT);

    if (curl) {
        json payload = {
            {"contents", {
                    {{"parts", {
                        {
                            {"text" , user_request}
                        }}}}
            }}
        };

        std::string payloadStr = payload.dump();

        struct curl_slist *headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payloadStr.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "CURL failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            json data = json::parse(response_string);
            try {
                std::string text = data["candidates"][0]["content"]["parts"][0]["text"];
                std::cout << "Response: " << text << std::endl;
            } catch (json::exception& e) {
                std::cerr << "json error: " << e.what() << std::endl;
                std::cerr << "Full json is: " << response_string << std::endl;
            }
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
