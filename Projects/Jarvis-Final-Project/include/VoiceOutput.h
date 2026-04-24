#pragma once
#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "Config.h"
#include <fstream>
#include <windows.h>

void playAudio(const std::string& filename) {
    mciSendStringA(("open \"" + filename + "\" type mpegvideo alias myAudio").c_str(), NULL, 0, NULL);
    mciSendStringA("play myAudio", NULL, 0, NULL);
}



class VoiceOutput {
        public:



            using json = nlohmann::json;

            static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
                size_t totalSize = size * nmemb;
                output->append((char*)contents, totalSize);
                return totalSize;
            }
            void speak(const std::string& botResponse) {
                std::string voiceId = "EXAVITQu4vr4xnSDxMaL";
                std::string url = "https://api.elevenlabs.io/v1/text-to-speech/" + voiceId; // Construct the URL for the specific voice using the voice ID


                CURL* curl = curl_easy_init(); // Initialize a CURL session
                CURLcode res; // Variable to hold the result of CURL operations
                std::string readBuffer; // String to hold the response data

                curl_global_init(CURL_GLOBAL_DEFAULT);
                curl = curl_easy_init(); // Initialize a CURL session

                // Check if CURL was initialized successfully
                if(curl) {
                    json payload = {
                        {"text", botResponse},
                        {"model_id", "eleven_multilingual_v2"},
                        {"voice_settings", {
                            {"stability", 0.75},
                            {"similarity_boost", 0.75}
                        }}
                    };


                    std::string jsonStr = payload.dump(); // Convert the JSON payload to a string for the POST request
                    // Set up the headers for the request, including the API key and content type
                    struct curl_slist* headers = NULL;
                    // Append the API key to the headers
                    headers = curl_slist_append(headers, ("xi-api-key: " + ELEVEN_LABS_API_KEY).c_str());
                    // Append the Accept header to specify that we want a JSON response
                    headers = curl_slist_append(headers, "Accept: application/json");
                    headers = curl_slist_append(headers, "Content-Type: application/json");
                    headers = curl_slist_append(headers, "accept: audio/mpeg");


                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                    curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // Set the URL for the request
                    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); // Set the headers for the request
                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // Set the callback function to handle the response data
                    // Set the CURL options for the request, including the URL,
                    // headers, and callback function to handle the response data
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer); // Set the string to hold the response data
                    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str()); // Set the JSON payload for the POST request
                    curl_easy_setopt(curl, CURLOPT_POST, 1L);



                    res = curl_easy_perform(curl); // Perform the CURL request and store the result in 'res'


                    if(res != CURLE_OK) { // Check if the request was successful
                        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl; // Print an error message if the request failed
                    } else {
                        if (readBuffer.find("{\"detail\":") != std::string::npos) { // Check if the response contains a JSON object (indicating an error)
                            std::cerr << "API Error: " << readBuffer << std::endl; // Print the error message from the API response
                        } else {
                            std::ofstream outFile("output.mp3", std::ios::binary); // Open a file to write the audio data
                            if (outFile.is_open()) { // Check if the file was opened successfully
                                outFile.write(readBuffer.c_str(), readBuffer.size()); // Write the audio data to the file
                                outFile.close(); // Close the file after writing
                                std::cout << "Audio saved to output.mp3" << std::endl; // Print a success message
                                ::playAudio("output.mp3"); // Call the function to play the audio file
                            } else {
                                std::cerr << "Failed to open output file." << std::endl; // Print an error message if the file could not be opened
                            }
                        }
                    }

                }
                curl_global_cleanup();
            }


};
