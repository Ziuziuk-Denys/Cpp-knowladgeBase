#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

int main() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.open-meteo.com/v1/forecast?latitude=51.5074&longitude=-0.1278&current_weather=true");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            try {
                double temp;
                double wind;
                auto jsonData = nlohmann::json::parse(readBuffer);
                if (jsonData.contains("current_weather")) {
                    temp = jsonData["current_weather"]["temperature"].get<double>();
                    wind = jsonData["current_weather"]["windspeed"].get<double>();
                    if (temp > 30) {
                        std::cout << "It's hot outside! Stay hydrated." << std::endl;
                    } else if (temp < 10) {
                        std::cout << "It's cold outside! Dress warmly." << std::endl;
                    } else {
                        std::cout << "The weather is moderate. Enjoy your day!" << std::endl;
                    }
                    if (wind > 20) {
                        std::cout << "It's windy outside! Hold onto your hat." << std::endl;
                    } else {
                        std::cout << "The wind speed is calm." << std::endl;
                    }
                } else {
                    std::cerr << "JSON does not contain 'current_weather' key." << std::endl;
                }
            } catch (const std::exception& e) {
                std::cerr << "JSON parsing error: " << e.what() << std::endl;
            }
        }
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize curl" << std::endl;
    }
    curl_global_cleanup();
    return 0;

}
