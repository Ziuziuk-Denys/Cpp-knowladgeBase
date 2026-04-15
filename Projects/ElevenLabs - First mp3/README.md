<p align="center">
  <img src="https://github.com/Ziuziuk-Denys/Cpp-knowladgeBase/blob/main/Assets/welcome_banner.gif?raw=true" width="100%" alt="Welcome Banner" />
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C++-ElevenLabs%20TTS-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
  <img src="https://img.shields.io/badge/Status-Working-success?style=for-the-badge" />
</p>

---

<h1 align="center">ElevenLabs First MP3</h1>

Yo guys! This is my first try to make text-to-speech with **ElevenLabs** API using C++.  
It sends text to ElevenLabs, gets back an MP3 file with a cool voice and saves it as `output.mp3`.

Super simple but already works! I used curl for HTTP requests and nlohmann/json for making the payload.  
This is my first real API project in C++ and I'm pretty happy with it.

---

<h1 align="center">What it does</h1>

- Takes a text ("Hello this is white cat, I'm gay")
- Sends it to ElevenLabs TTS API
- Uses a specific voice (EXAVITQu4vr4xnSDxMaL)
- Gets the audio back as MP3
- Saves it to `output.mp3` in the same folder

---

<h1 align="center">How to build and run</h1>

1. Put your ElevenLabs API key in `config.h`
2. Make sure you have **libcurl** and **nlohmann_json** installed
3. Build with CMake:

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

4. Run the executable — it will create `output.mp3`

---

<h1 align="center">Project Files</h1>

- `main.cpp` — the main code (with tons of comments)
- `config.h` — where I store my secret API key
- `CMakeLists.txt` — build instructions

---

<h1 align="center">Fully Commented main.cpp</h1>

Here is the **complete code** with **a shitload of comments** so even a total beginner can understand every single line:

```cpp
#include <iostream>              // For cout and cerr (printing to console)
#include <curl/curl.h>           // Main library for making HTTP requests (POST to API)
#include <nlohmann/json.hpp>     // Super cool library to work with JSON easily
#include "config.h"              // My file where the API key is stored
#include <fstream>               // For saving the MP3 file to disk

using json = nlohmann::json;     // Shortcut so I don't have to write nlohmann::json every time

// Callback function that curl calls every time it receives some data from the server
// This is needed because the MP3 can be big and come in small chunks
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) { 
    // NOLINT(readability-non-const-parameter)  // Just to shut up the linter
    
    // Calculate how many bytes we received this time
    size_t totalSize = size * nmemb;
    
    // Add these bytes to our string buffer
    output->append((char*)contents, totalSize);
    
    // Tell curl we processed all the data
    return totalSize;
}

int main() {
    // The voice ID I want to use (you can change it to any other ElevenLabs voice)
    std::string voiceId = "EXAVITQu4vr4xnSDxMaL"; 
    
    // Build the full URL for the Text-to-Speech endpoint
    std::string url = "https://api.elevenlabs.io/v1/text-to-speech/" + voiceId;

    // Variables we will need
    CURL* curl = nullptr;        // Pointer to the curl session
    CURLcode res;                // Variable to store if the request was successful or not
    std::string readBuffer;      // This string will hold the raw MP3 data we get back

    // Initialize curl globally (must be done once)
    curl_global_init(CURL_GLOBAL_DEFAULT);
    
    curl = curl_easy_init();     // Create a new curl session

    // Check if curl started successfully
    if (curl) {
        
        // Create the JSON payload that we send to the API
        json payload = {
            {"text", "Hello this is white cat, I'm gay"},   // The text we want to speak
            {"model_id", "eleven_multilingual_v2"},         // Which AI model to use (good for many languages)
            {"voice_settings", {                            // Settings that control how the voice sounds
                {"stability", 0.75},                        // How stable/emotional the voice is
                {"similarity_boost", 0.75}                  // How much it tries to sound like the original voice
            }}
        };

        // Convert our JSON object into a normal string so curl can send it
        std::string jsonStr = payload.dump();

        // Prepare headers for the request
        struct curl_slist* headers = NULL;
        
        // Add our secret API key (comes from config.h)
        headers = curl_slist_append(headers, ("xi-api-key: " + apiKey).c_str());
        
        // Tell the server what we accept and what we are sending
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "accept: audio/mpeg");   // We expect MP3 audio back

        // Now we set all options for this request
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());                    // Where to send the request
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);                 // Add all our headers
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);       // Use our callback to receive data
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);              // Put received data into readBuffer
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());         // Send the JSON as the body
        curl_easy_setopt(curl, CURLOPT_POST, 1L);                            // This is a POST request

        // Actually send the request to ElevenLabs
        res = curl_easy_perform(curl);

        // Check if something went wrong with the connection
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } 
        else {
            // Check if the server returned an error message (starts with {"detail": )
            if (readBuffer.find("{\"detail\":") != std::string::npos) {
                std::cerr << "API Error: " << readBuffer << std::endl;
            } 
            else {
                // Everything is good! Save the audio to a file
                std::ofstream outFile("output.mp3", std::ios::binary);
                
                if (outFile.is_open()) {
                    outFile.write(readBuffer.c_str(), readBuffer.size());  // Write all bytes
                    outFile.close();
                    std::cout << "Audio saved to output.mp3" << std::endl;
                    std::cout << "Check the file in the same folder!" << std::endl;
                } 
                else {
                    std::cerr << "Failed to open output file." << std::endl;
                }
            }
        }
    }

    // Clean up curl stuff
    curl_global_cleanup();
    
    return 0;   // Program finished successfully
}
```

---

<h1 align="center">config.h</h1>

```cpp
#pragma once

#include <string>

std::string apiKey = "sk_b4598f5c527049c701b56109bfbf7b3fccac899898e2cb01";  // ← Put your real key here
```

---

<h1 align="center">CMakeLists.txt (example)</h1>

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
  <b>Made by Denys </b><br>
  My first real API project in C++ • Learning high-performance stuff
</p>

