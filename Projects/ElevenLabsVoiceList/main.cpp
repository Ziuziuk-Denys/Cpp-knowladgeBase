#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "config.h"

// Callback function to write the response data into a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) { // NOLINT(readability-non-const-parameter)
    // Calculate the total size of the data
    size_t totalSize = size * nmemb;
    // Append the data to the output string
    output->append((char*)contents, totalSize);
    // Return the total size of the data processed
    return totalSize;
}

// Main function to perform the API request and process the response
int main() {
    // Initialize CURL and set up the request
    CURL* curl;
    // Variable to hold the result of the CURL operation
    CURLcode res;
    // String to hold the response data
    std::string readBuffer;
    // Initialize CURL globally
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    // Check if CURL was initialized successfully
    if(curl) {
        // Set up the headers for the request, including the API key and content type
        struct curl_slist* headers = NULL;
        // Append the API key to the headers
        headers = curl_slist_append(headers, ("xi-api-key: " + apiKey).c_str());
        // Append the Accept header to specify that we want a JSON response
        headers = curl_slist_append(headers, "Accept: application/json");

        // Set the CURL options for the request, including the URL, headers, and callback function to handle the response data
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.elevenlabs.io/v1/voices");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        // Check if the CURL request was successful
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            // Try to parse the response data as JSON and extract the relevant information about the voices
            try {
                // Parse the response data as JSON
                auto jsonResponse = nlohmann::json::parse(readBuffer);
                // Create a vector to hold the information about each voice and populate it by iterating through the "voices" array in the JSON response
                std::vector<std::string> voiceInfoList;
                // Iterate through each voice in the "voices" array and extract the name, ID, and category, then format this information into a string and add it to the voiceInfoList vector
                for (const auto& voice : jsonResponse["voices"]) {
                    std::string voiceInfo = "Name: " + voice["name"].get<std::string>() + ", ID: " + voice["voice_id"].get<std::string>() + ", Category: " + voice["category"].get<std::string>();
                    voiceInfoList.push_back(voiceInfo);
                }

                // Print the information about each voice to the console
                for (size_t i = 0; i < voiceInfoList.size(); ++i) {
                    std::cout << voiceInfoList[i] << std::endl;
                }

            // Catch any exceptions that occur during JSON parsing and print an error message to the console
            } catch (const nlohmann::json::parse_error& e) {
                std::cerr << "JSON parse error: " << e.what() << std::endl;
            }
        }
        // Clean up the CURL resources and free the headers list before exiting the program
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
        return 0;
    }
}
