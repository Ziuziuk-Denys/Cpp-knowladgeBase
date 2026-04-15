<p align="center">
  <img src="https://media1.giphy.com/media/v1.Y2lkPTc5MGI3NjExZHBzeWp6N2xhcnB1Mnc0OG43azQ3dnBzcWdqOTBhODYzdzdnam0yeiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/aEqhXX8g7J2D0QuhxI/giphy.gif?raw=true" width="100%" alt="Idk" />
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C++-Gemini%20API-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
  <img src="https://img.shields.io/badge/Status-Working-success?style=for-the-badge" />
</p>

---

<h1 align="center">Gemini First Message</h1>

Yo guys! This is my first project where I talk to **Google's Gemini AI** directly from C++.  
I type a question in the console and the AI answers me back. Super cool!

I added **TONS of comments** again so even I can understand every single line later.

---

<h1 align="center">Fully Commented main.cpp</h1>

```cpp
#include <iostream>          // For printing to console and reading user input
#include <curl/curl.h>       // Library to send HTTP requests to the internet
#include <nlohmann/json.hpp> // Super useful library to work with JSON data easily
#include "config.h"          // My file where the Gemini API key is stored

using json = nlohmann::json; // Short name so I don't have to write nlohmann::json every time

// ===================================================================
// CALLBACK FUNCTION
// Curl calls this every time it receives data from Gemini
// ===================================================================
size_t WriteCallback(void *contents,     // Pointer to the raw bytes we received
                     size_t size,        // Size of each block (usually 1 byte)
                     size_t nmemb,       // How many blocks we received this time
                     std::string* output) // Our string where we collect the full response
{
    size_t totalSize = size * nmemb;           // Calculate real number of bytes
    output->append((char*)contents, totalSize); // Add this chunk to our response string
    return totalSize;                          // Tell curl we processed everything
}

int main() {
    std::string model = "gemini-2.5-flash";   // Which Gemini model we want to use
    std::string response_string;              // This will hold the full JSON answer from Gemini

    // Build the full URL with our API key from config.h
    std::string url = "https://generativelanguage.googleapis.com/v1beta/models/" 
                    + model + ":generateContent?key=" + GEMINI_API;

    // Ask the user for a question
    std::string user_request = "";
    std::cout << "Enter your qestion: ";
    std::cin >> user_request;                 // Read one word (note: only one word for now)

    // ====================== INITIALIZE CURL ======================
    CURL *curl = curl_easy_init();            // Create a new curl session
    curl_global_init(CURL_GLOBAL_DEFAULT);    // Prepare curl library (must be done once)

    if (curl) {
        // ====================== CREATE JSON PAYLOAD ======================
        json payload = {
            {"contents", {
                {{"parts", {
                    {
                        {"text", user_request}    // The question we typed
                    }
                }}}
            }}
        };

        std::string payloadStr = payload.dump();  // Convert JSON object to string

        // ====================== HEADERS ======================
        struct curl_slist *headers = nullptr;     // Empty list of headers
        headers = curl_slist_append(headers, "Content-Type: application/json");

        // ====================== SET ALL CURL OPTIONS ======================
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());              // Where to send request
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payloadStr.c_str()); // JSON data to send
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);           // Add our headers
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);  // Use our callback
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);   // Put answer here

        // ====================== SEND REQUEST ======================
        CURLcode res = curl_easy_perform(curl);   // Actually send everything to Gemini

        if (res != CURLE_OK) {
            std::cerr << "CURL failed: " << curl_easy_strerror(res) << std::endl;
        } 
        else {
            // Try to parse the JSON response
            json data = json::parse(response_string);
            try {
                // Extract the text answer from the deep nested JSON
                std::string text = data["candidates"][0]["content"]["parts"][0]["text"];
                std::cout << "Response: " << text << std::endl;
            } 
            catch (json::exception& e) {
                std::cerr << "json error: " << e.what() << std::endl;
                std::cerr << "Full json is: " << response_string << std::endl;
            }
        }

        // Clean up
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
```

---

<h1 align="center">Other files</h1>

**config.h**
```cpp
#include <string>

// Your Gemini API key (get it from Google AI Studio)
std::string GEMINI_API = "YOUR_API";
```

**CMakeLists.txt**
```cmake
# Minimum CMake version we need
cmake_minimum_required(VERSION 3.20)

# Name of the project
project(Gemini)

# Use C++20 standard
set(CMAKE_CXX_STANDARD 20)

# Find the libraries we need
find_package(CURL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# Create the executable
add_executable(Gemini main.cpp config.h)

# Link the libraries
target_link_libraries(Gemini PRIVATE
        CURL::libcurl
        nlohmann_json::nlohmann_json
)
```

---

<p align="center">
  <img src="https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png" width="100%" />
</p>

<p align="center">
  <b>Made by Denys</b><br>
  My first Gemini AI project in C++ • Learning step by step
</p>
