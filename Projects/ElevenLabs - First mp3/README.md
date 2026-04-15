<p align="center">
  <img src="https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExeWowbXg5Mml1d213eThhdmNpMTlzbmxzZ3k1ODd1aHNlNzdhYjh4aiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/8nRxogx9tgvCzuSHLl/giphy.gif?raw=true" width="100%" alt="Idk" />
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C++-ElevenLabs%20TTS-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
  <img src="https://img.shields.io/badge/Status-Working-success?style=for-the-badge" />
</p>

---

<h1 align="center">ElevenLabs First MP3</h1>

Yo guys! This is my first project where I make the computer speak using **ElevenLabs** API in C++.  
I send some text, and it gives me back an MP3 file with a cool voice.

I added **TONS of comments** so even I can understand everything later.

---

<h1 align="center">Fully Commented main.cpp</h1>

```cpp
#include <iostream>              // Allows us to print text to the console with std::cout and std::cerr
#include <curl/curl.h>           // Library that lets us talk to websites (send HTTP requests)
#include <nlohmann/json.hpp>     // Awesome library to easily create and read JSON data
#include "config.h"              // My own file where I keep the secret API key
#include <fstream>               // Needed to save the MP3 file to the hard drive

using json = nlohmann::json;     // Short name so I don't have to type nlohmann::json every time

// ===================================================================
// CALLBACK FUNCTION
// Curl calls this function every time it receives a piece of data from the server
// ===================================================================
size_t WriteCallback(
    void* contents,           // Pointer to the chunk of data we just received (raw bytes)
    size_t size,              // Size of each "item" in bytes (usually 1)
    size_t nmemb,             // Number of items in this chunk
    std::string* output)      // Pointer to our string where we want to store all received data
{
    // Calculate real size of this chunk in bytes
    // Example: if size = 1 and nmemb = 1024 → totalSize = 1024 bytes
    size_t totalSize = size * nmemb;

    // Add this chunk to the end of our string
    // (char*)contents converts the void* pointer to something we can read as characters
    output->append((char*)contents, totalSize);

    // We must return how many bytes we actually processed
    // If we return less than totalSize, curl thinks something went wrong
    return totalSize;
}

int main()
{
    // ====================== VARIABLES ======================
    
    std::string voiceId = "EXAVITQu4vr4xnSDxMaL";   
    // This is the ID of the voice I want to use. 
    // You can find other voice IDs on ElevenLabs website.

    std::string url = "https://api.elevenlabs.io/v1/text-to-speech/" + voiceId;  
    // We build the full address where we send the request.
    // Example: https://api.elevenlabs.io/v1/text-to-speech/EXAVITQu4vr4xnSDxMaL

    CURL* curl = nullptr;        
    // This is a pointer to the CURL session. 
    // Think of it as "the connection" to the internet. 
    // We set it to nullptr first because we haven't created it yet.

    CURLcode res;                
    // This variable will store the result of the request.
    // CURLE_OK means everything went fine. Other values = error.

    std::string readBuffer;      
    // This string will collect all the data (MP3 bytes) that the server sends us.
    // At the end it will contain the whole audio file.

    // ====================== INITIALIZATION ======================
    
    curl_global_init(CURL_GLOBAL_DEFAULT);   
    // We must call this once before using any curl functions.
    // It prepares some global stuff inside the library.

    curl = curl_easy_init();     
    // Creates a new easy curl session. 
    // Now "curl" pointer actually points to a working connection.

    // Check if we successfully created the curl session
    if (curl) 
    {
        // ====================== CREATE JSON PAYLOAD ======================
        
        json payload = {
            {"text", "Hello! This is a test"},     // The text we want the AI to say
            {"model_id", "eleven_multilingual_v2"},           // Which AI model should speak (this one is good)
            {"voice_settings", {                              // How the voice should sound
                {"stability", 0.75},                          // 0.0 = very emotional, 1.0 = very stable/calm
                {"similarity_boost", 0.75}                    // How close to the original voice it should be
            }}
        };

        std::string jsonStr = payload.dump();   
        // .dump() turns our json object into a normal text string 
        // so we can send it to the server.

        // ====================== HEADERS ======================
        
        struct curl_slist* headers = NULL;   
        // This is a linked list of HTTP headers. Starts empty.

        headers = curl_slist_append(headers, ("xi-api-key: " + apiKey).c_str());  
        // Adds our secret API key so ElevenLabs knows it's really us.

        headers = curl_slist_append(headers, "Accept: application/json");        
        headers = curl_slist_append(headers, "Content-Type: application/json");  
        headers = curl_slist_append(headers, "accept: audio/mpeg");              
        // These tell the server what format we are sending and what we want back.

        // ====================== SET OPTIONS ======================
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());                    
        // Tells curl where to send the request (the full web address).

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);                 
        // Gives curl all the headers we created above.

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);       
        // Tells curl to call our WriteCallback function when data arrives.

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);              
        // Tells the callback where to put the received data (our readBuffer string).

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());         
        // The actual data (JSON) we are sending in the request body.

        curl_easy_setopt(curl, CURLOPT_POST, 1L);                            
        // Tells curl this is a POST request (not GET).

        // ====================== SEND THE REQUEST ======================
        
        res = curl_easy_perform(curl);   
        // This is the moment we actually send everything to ElevenLabs!

        // ====================== CHECK RESULT ======================
        
        if (res != CURLE_OK) {
            // Something went wrong with the connection
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } 
        else {
            // We got a response. Now check if it's an error or real audio.
            
            if (readBuffer.find("{\"detail\":") != std::string::npos) {
                // If the response starts with {"detail": it means the API returned an error
                std::cerr << "API Error: " << readBuffer << std::endl;
            } 
            else {
                // Success! The data in readBuffer is the MP3 file.
                
                std::ofstream outFile("output.mp3", std::ios::binary);  
                // Open (or create) a file called output.mp3 in binary mode

                if (outFile.is_open()) {
                    outFile.write(readBuffer.c_str(), readBuffer.size());  
                    // Write all bytes from readBuffer into the file
                    outFile.close();                                       
                    // Close the file so everything is saved properly
                    
                    std::cout << "Audio saved to output.mp3" << std::endl;
                    std::cout << "Go check the file in the folder!" << std::endl;
                } 
                else {
                    std::cerr << "Failed to open output file." << std::endl;
                }
            }
        }
    }

    // ====================== CLEAN UP ======================
    curl_global_cleanup();   // Free all global resources used by curl
    // Note: we don't need to call curl_easy_cleanup(curl) here because 
    // the program is ending anyway, but it's good practice in bigger projects.

    return 0;   // Everything went well, program ends successfully
}
```

---

<h1 align="center">Other files</h1>

**config.h**
```cpp
#pragma once
#include <string>

std::string apiKey = "sk_b4598f5c527049c701b56109bfbf7b3fccac899898e2cb01";
```

**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 3.20)
project(ElevenLabs_First_MP3)

set(CMAKE_CXX_STANDARD 20)

find_package(CURL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(ElevenLabs_First_MP3 main.cpp)

target_link_libraries(ElevenLabs_First_MP3 PRIVATE 
    CURL::libcurl 
    nlohmann_json::nlohmann_json
)
```

---

<p align="center">
  <img src="https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png" width="100%" />
</p>

<p align="center">
  <b>Made by Denys)</b><br>
  My first API project • Learning C++ step by step
</p>
