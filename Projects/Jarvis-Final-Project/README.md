<p align="center">
  <img src="https://media1.giphy.com/media/v1.Y2lkPTc5MGI3NjExMDkxNzZ0a3VhdnBvYnprMjRweTA5cTUybjl3ZXR0MDNlYnlvbnN0dyZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/VrtvDMP4ajo5y/giphy.gif" width="100%" alt="Jarvis Banner" />
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C++-Jarvis%20Voice%20Assistant-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
  <img src="https://img.shields.io/badge/Status-Working-success?style=for-the-badge" />
  <img src="https://img.shields.io/badge/AI-Gemini%202.5%20Flash-blueviolet?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Voice-ElevenLabs-orange?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Speech-Vosk-44CC11?style=for-the-badge" />
</p>

---

<h1 align="center">What is this?</h1>

Yo! This is my most advanced C++ project so far. I built a **real voice assistant** that runs right in the console - like an actual Jarvis from Iron Man, except mine actually works!

Here's how the whole thing works in simple terms:

> You hit **Enter** → speak into the mic → the program records your voice → converts it to text → sends that text to **Gemini AI** → gets an answer back → **ElevenLabs** reads the answer out loud in a real human voice.

That's it. One full loop - and you've got a working AI voice assistant written in C++.

---

<h1 align="center">Tech Stack</h1>

<p align="center">
  <a href="https://skillicons.dev">
    <img src="https://skillicons.dev/icons?i=cpp,cmake,github,git,windows" />
  </a>
</p>

| Library | What it does | Where I use it |
| :--- | :--- | :--- |
| <img src="https://img.shields.io/badge/-miniaudio-00599C?style=flat-square" /> | Records audio from the microphone | `Recorder.h` |
| <img src="https://img.shields.io/badge/-Vosk-44CC11?style=flat-square" /> | Converts speech to text (works offline!) | `Transcriber.h` |
| <img src="https://img.shields.io/badge/-Gemini%20API-blueviolet?style=flat-square" /> | The actual AI brain that answers questions | `Brain.h` |
| <img src="https://img.shields.io/badge/-ElevenLabs%20API-orange?style=flat-square" /> | Converts AI text response back to speech | `VoiceOutput.h` |
| <img src="https://img.shields.io/badge/-libcurl-red?style=flat-square" /> | Sends HTTP requests to both APIs | `Brain.h`, `VoiceOutput.h` |
| <img src="https://img.shields.io/badge/-nlohmann%2Fjson-9cf?style=flat-square" /> | Parses and builds JSON payloads | `Brain.h`, `VoiceOutput.h`, `Transcriber.h` |
| <img src="https://img.shields.io/badge/-WinMM-lightgrey?style=flat-square" /> | Plays the `.mp3` audio file on Windows | `VoiceOutput.h` |

---

<h1 align="center">Project Structure</h1>

```
Jarvis_Final/
├── src/
│   └── main.cpp          ← Entry point. The main loop lives here.
├── include/
│   ├── Config.h          ← All API keys stored here
│   ├── Recorder.h        ← Microphone recording logic
│   ├── Transcriber.h     ← Speech-to-text using Vosk
│   ├── Brain.h           ← Sends text to Gemini, gets answer back
│   └── VoiceOutput.h     ← Sends answer to ElevenLabs, plays audio
├── libs/
│   └── vosk/             ← Vosk library + DLLs
│       ├── vosk_api.h
│       ├── vosk.dll
│       └── ...
├── model/                ← Vosk speech recognition model folder
└── CMakeLists.txt        ← Build config
```

---

<h1 align="center">How The Flow Works</h1>

```
[ User hits Enter ]
        ↓
[ Recorder.h ] ──── miniaudio captures mic → stores raw audio in fullRecording vector
        ↓
[ Transcriber.h ] ── Vosk model reads the audio bytes → returns recognized text string
        ↓
[ Brain.h ] ──────── Sends text to Gemini API via curl → gets AI response string back
        ↓
[ VoiceOutput.h ] ── Sends response to ElevenLabs API → saves output.mp3 → plays it
        ↓
[ Loop repeats - Jarvis is ready for the next question ]
```

---

<h1 align="center">CMakeLists.txt</h1>

This is the build configuration file. CMake reads it and knows how to compile the project, find libraries, and link everything together.

```cmake
# Minimum version of CMake needed to build this project
cmake_minimum_required(VERSION 3.20)

# The name of our project
project(Jarvis_Final)

# We're using C++20 - needed for some modern features
set(CMAKE_CXX_STANDARD 20)

# Tell CMake to find the libcurl library on this machine
# REQUIRED means - if it's not found, stop and throw an error
find_package(CURL REQUIRED)

# Tell CMake to find nlohmann/json - our JSON parsing library
find_package(nlohmann_json CONFIG REQUIRED)

# We're using Vosk as a local library (not installed system-wide)
# VOSK_DIR points to the folder where we dropped the .dll and .h files
set(VOSK_DIR "${CMAKE_SOURCE_DIR}/libs/vosk")

# Look for the vosk_api.h header inside our libs/vosk folder only
# NO_DEFAULT_PATH means - don't search anywhere else on the system
find_path(VOSK_INCLUDE_DIR NAMES vosk_api.h PATHS ${VOSK_DIR} NO_DEFAULT_PATH)

# Look for the compiled vosk library (.lib or .dll) inside our folder
find_library(VOSK_LIBRARY NAMES vosk PATHS ${VOSK_DIR} NO_DEFAULT_PATH)

# Create the actual executable called "Jarvis"
# List all source files and headers that belong to this project
add_executable(Jarvis
        src/main.cpp          # Main loop - entry point
        include/Config.h      # API keys
        include/Recorder.h    # Mic recording
        include/Transcriber.h # Speech-to-text
        include/Brain.h       # Gemini API
        include/VoiceOutput.h # ElevenLabs + audio playback
)

# Tell the compiler where to find our header files
# PRIVATE means - only this target (Jarvis) needs these include paths
target_include_directories(Jarvis PRIVATE include ${VOSK_INCLUDE_DIR})

# Link all the external libraries to our Jarvis executable
target_link_libraries(Jarvis PRIVATE
        CURL::libcurl                  # For sending HTTP requests (APIs)
        nlohmann_json::nlohmann_json   # For reading and building JSON
        ${VOSK_LIBRARY}                # For speech recognition (Vosk)
        winmm.lib                      # Windows Multimedia - for playing audio
)

# After the build is done, copy required DLL files into the output folder
# This way the .exe file actually finds them at runtime without manual copy-paste
add_custom_command(TARGET Jarvis POST_BUILD
        # Copy the main Vosk DLL (renamed to libvosk.dll - that's what it expects at runtime)
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${VOSK_DIR}/vosk.dll" "$<TARGET_FILE_DIR:Jarvis>/libvosk.dll"

        # Copy MinGW runtime DLLs that Vosk depends on internally
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${VOSK_DIR}/libgcc_s_seh-1.dll" "$<TARGET_FILE_DIR:Jarvis>/libgcc_s_seh-1.dll"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${VOSK_DIR}/libstdc++-6.dll" "$<TARGET_FILE_DIR:Jarvis>/libstdc++-6.dll"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${VOSK_DIR}/libwinpthread-1.dll" "$<TARGET_FILE_DIR:Jarvis>/libwinpthread-1.dll"
)
```

---

<h1 align="center">Config.h</h1>

This file stores all the API keys and voice settings. It's included wherever we need to talk to an external service.

```cpp
// Header guard - makes sure this file is only included once
// even if multiple files try to #include it at the same time
#ifndef CONFIG_H
#define CONFIG_H

#include <string>

// =============================================
// GEMINI API KEY
// Get yours at: https://aistudio.google.com
// This key authenticates our requests to Google's Gemini AI
// =============================================
const std::string GEMINI_API_KEY = "YOUR_GEMINI_KEY_HERE";

// =============================================
// ELEVEN LABS API KEY
// Get yours at: https://elevenlabs.io
// This key authenticates our requests to the ElevenLabs TTS API
// =============================================
const std::string ELEVEN_LABS_API_KEY = "YOUR_ELEVENLABS_KEY_HERE";

// =============================================
// ELEVEN LABS VOICE ID
// Each voice on ElevenLabs has a unique string ID
// This one is "Rachel" - a natural-sounding English voice
// Find other voice IDs in your ElevenLabs dashboard under Voices
// =============================================
const std::string ELEVEN_LABS_VOICE_ID = "EXAVITQu4vr4xnSDxMaL";

// End of the header guard
#endif // CONFIG_H
```

---

<h1 align="center">main.cpp</h1>

This is the entry point of the whole program. It creates all the objects and runs an infinite loop - record, transcribe, ask AI, speak the answer, repeat forever until you close the console.

```cpp
#include <iostream>   // For printing stuff to the console (std::cout, std::cerr)
#include <vector>     // For std::vector - the container that holds our raw audio bytes
#include <string>     // For std::string - holds transcribed text and AI responses

// Our own header files - each one handles one step of the pipeline
#include "Config.h"       // API keys - needed here for curl_global_init
#include "Recorder.h"     // Microphone recording
#include "Transcriber.h"  // Speech-to-text conversion
#include "Brain.h"        // Gemini AI communication
#include "VoiceOutput.h"  // ElevenLabs TTS + audio playback

// Global vector that holds the raw audio bytes captured from the microphone
// It's global because the miniaudio callback (which runs on a separate audio thread)
// needs to write into it - and callbacks can't easily receive custom parameters
std::vector<char> fullRecording;

int main() {
    // Initialize libcurl globally - must be done ONCE before any curl call anywhere in the program
    // It sets up SSL, sockets, and all the networking internals
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create our AI brain - handles communication with Gemini
    Brain brain;

    // Create our voice output - handles ElevenLabs and audio playback
    VoiceOutput voiceOutput;

    // Wrap everything in try-catch so if something throws an exception,
    // we print a readable message instead of the program just silently dying
    try {
        // Infinite loop - Jarvis keeps listening until you close the console
        while (true) {
            // Prompt the user to press Enter when ready to speak
            std::cout << "Hit Enter to start recording" << std::endl;

            // Block here and wait until the user presses Enter
            std::cin.get();

            // Clear the audio buffer before each new recording
            // Without this, old audio from the previous round would still be in there
            fullRecording.clear();

            // Start recording from the microphone
            // This function blocks until the user presses Enter again to stop
            // While running, the audio callback fills fullRecording with raw 16-bit PCM bytes
            startRecording();

            // Safety check - if we somehow recorded nothing, skip this round
            if (fullRecording.empty()) {
                std::cout << "Recording is empty, try again" << std::endl;
                continue; // Jump back to the top of the while loop
            }

            // Send the raw audio bytes to Vosk and get back the recognized words as a string
            std::string userText = convertAudioToText(fullRecording);

            // Safety check - if Vosk couldn't make out any words, skip this round
            if (userText.empty()) {
                std::cout << "Unable to clarify text" << std::endl;
                continue; // Jump back to the top of the while loop
            }

            // Print what the user said so we can verify transcription is working
            std::cout << "You: " << userText << std::endl;

            // Send the transcribed text to Gemini and wait for a response
            // The answer gets saved into brain.gemini_response internally
            brain.askGemini(userText);

            // Grab the answer string from the Brain object
            std::string answer = brain.gemini_response;

            // Safety check - if Gemini returned nothing, skip this round
            if (answer.empty()) {
                std::cout << "I don't know" << std::endl;
                continue; // Jump back to the top of the while loop
            }

            // Send Gemini's answer to ElevenLabs
            // It converts the text to speech, saves it as output.mp3, and plays it
            voiceOutput.speak(answer);

            // Confirm the full cycle completed
            std::cout << "Here we go." << std::endl;

            // Back to the top - ready for the next question
        }

    } catch (const std::exception& e) {
        // Catch any exception thrown anywhere in the loop
        // Print the error message so we know what broke
        std::cerr << "Critical error: " << e.what() << std::endl;
    }

    // Clean up the curl library - frees all memory curl allocated during init
    curl_global_cleanup();

    // Pause so the console doesn't immediately close - we can read any last output
    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();

    return 0; // Program exited cleanly
}
```

---

<h1 align="center">Recorder.h</h1>

This file handles everything microphone-related. It uses the **miniaudio** library - a single-header audio library that works on Windows, Mac, and Linux - to capture raw audio from your mic and store it in the global `fullRecording` vector.

```cpp
#pragma once          // Modern header guard - tells the compiler to include this file only once
#include <iostream>   // For printing status messages to the console
#include <vector>     // For std::vector - the container holding our raw audio bytes

// miniaudio is a single-header library - all its code lives in one .h file
// MINIAUDIO_IMPLEMENTATION must be defined in EXACTLY ONE place before including it
// This tells the compiler: "put the actual function bodies here"
// If you define this in two places, you'll get duplicate symbol linker errors
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

// This is the global audio buffer defined in main.cpp
// extern means: "I know this variable exists somewhere else - let me use it"
// We don't define it here - we just borrow it
extern std::vector<char> fullRecording;

// =========================================================
// DATA CALLBACK FUNCTION
// miniaudio calls this automatically every time a new batch
// of audio frames arrives from the microphone hardware.
// IMPORTANT: This runs on a background audio thread - not main thread!
// So keep it fast and never do heavy processing inside it.
// =========================================================
void dataCallback(ma_device* device,      // Pointer to the audio device doing the capture
                  void* output,           // Output buffer - NULL here, we're capturing not playing
                  const void* input,      // The fresh audio data that just came from the mic
                  ma_uint32 frameCount)   // How many audio frames arrived this time
{
    // If there's no input data, there's nothing to do - just return
    if (input == NULL) return;

    // Calculate how many bytes one audio frame takes
    // Our format is s16 (16-bit signed int) mono = 2 bytes per frame
    size_t bytesPerFrame = ma_get_bytes_per_frame(device->capture.format, device->capture.channels);

    // Total byte count for this batch = frames × bytes per frame
    size_t bytesToCopy = frameCount * bytesPerFrame;

    // Cast the raw void* pointer to char* so we can treat it as a byte array
    const char* inputData = (const char*)input;

    // Append this batch of audio bytes to the back of our global recording buffer
    // After recording stops, fullRecording holds the entire audio session as raw bytes
    fullRecording.insert(fullRecording.end(), inputData, inputData + bytesToCopy);
}

// =========================================================
// START RECORDING FUNCTION
// Configures the mic, starts capturing audio into fullRecording,
// waits for the user to press Enter, then stops everything cleanly.
// =========================================================
void startRecording() {
    // Create a device config for capture mode (recording, not playback)
    ma_device_config deviceConfig = ma_device_config_init(ma_device_type_capture);

    // Use 16-bit signed integer format for audio samples
    // This is the standard format for speech recognition - Vosk expects exactly this
    deviceConfig.capture.format = ma_format_s16;

    // Mono audio - one channel is plenty for voice recognition
    deviceConfig.capture.channels = 1;

    // 16000 Hz sample rate - this is what Vosk's models are trained on
    // Recording at a different rate would cause garbled/wrong transcription results
    deviceConfig.sampleRate = 16000;

    // Register our callback - miniaudio will call it automatically with new audio chunks
    deviceConfig.dataCallback = dataCallback;

    // Initialize the actual audio device using our config
    // NULL for first parameter means "use the default mic"
    ma_device device;
    if (ma_device_init(NULL, &deviceConfig, &device) == MA_SUCCESS) {

        // Start the device - audio begins flowing into our callback right now
        ma_device_start(&device);

        std::cout << "Recording... Press Enter to stop." << std::endl;

        // Block here until the user presses Enter - audio keeps being captured in background
        std::cin.get();

        // Stop audio capture
        ma_device_stop(&device);

        // Free all resources used by the audio device - always clean up!
        ma_device_uninit(&device);

    } else {
        // Device initialization failed - usually means no mic found or driver issue
        std::cerr << "Failed to initialize capture device." << std::endl;
    }
}
```

---

<h1 align="center">Transcriber.h</h1>

This file takes the raw audio bytes stored in `fullRecording` and converts them into a plain text string using **Vosk** - an offline speech recognition library. The cool thing about Vosk is that it works completely without internet. All the AI model files are stored locally in the `model/` folder.

```cpp
#pragma once
#include <vosk_api.h>         // The Vosk speech recognition C API - loads and runs the model
#include <vector>             // For std::vector - holds our raw audio bytes
#include <iostream>           // For printing debug info to the console
#include <nlohmann/json.hpp>  // For parsing the JSON result Vosk returns

// =========================================================
// CONVERT AUDIO TO TEXT
// Takes the raw 16-bit PCM audio bytes and runs them through
// the Vosk offline speech recognition model.
// Returns a plain string of the recognized words.
// =========================================================
std::string convertAudioToText(std::vector<char> fullRecording) {

    std::string text; // This will hold the final recognized text we return

    // Print the byte count so we can verify something was actually recorded
    // If this prints 0, the recording step failed somewhere
    std::cout << "Recording size: " << fullRecording.size() << " bytes" << std::endl;

    // Load the Vosk language model from the "model" folder
    // This folder contains all the neural network files for speech recognition
    // Make sure "model" exists next to your .exe or this will crash with NULL
    VoskModel* model = vosk_model_new("model");

    // Create a recognizer using the loaded model
    // 16000.0f is the sample rate - MUST match what we recorded in Recorder.h
    // If these don't match, Vosk will process the audio at the wrong speed = garbage output
    VoskRecognizer* recognizer = vosk_recognizer_new(model, 16000.0);

    // Feed the entire recorded audio to Vosk in one go
    // .data() gives a raw pointer to the vector's byte array
    // .size() tells Vosk exactly how many bytes to process
    // Returns 1 if it finished processing everything, 0 if there's more to process
    int completed = vosk_recognizer_accept_waveform(recognizer, fullRecording.data(), fullRecording.size());

    // Get the recognition result based on whether Vosk is done or not
    const char* result;
    if (completed) {
        // Vosk processed everything successfully - get the final clean result
        result = vosk_recognizer_result(recognizer);
    } else {
        // Vosk didn't fully finish - ask for whatever it recognized so far
        // This is the "partial" final result, still useful in practice
        result = vosk_recognizer_final_result(recognizer);
    }

    // Print the raw JSON Vosk gives us - good for debugging
    // Example output: {"text": "hey what is the weather today"}
    std::cout << "Recognized JSON: " << result << std::endl;

    // Parse the raw C string as JSON using nlohmann/json
    nlohmann::json jsonData = nlohmann::json::parse(result);

    // Extract just the "text" field - that's the plain recognized string we want
    if (jsonData.contains("text")) {
        text = jsonData["text"].get<std::string>();
    } else {
        // Fallback in case Vosk returned something unexpected - use the raw result
        text = result;
    }

    // Free the recognizer object - important to avoid memory leaks
    vosk_recognizer_free(recognizer);

    // Free the model - it takes a lot of memory, so always release it when done
    vosk_model_free(model);

    // Return the clean recognized text string to main.cpp
    return text;
}
```

---

<h1 align="center">Brain.h</h1>

This is the AI brain of the whole project. It takes the transcribed text, packages it into a JSON request, sends it to **Google's Gemini API** over HTTP using libcurl, parses the response, and stores the answer in `gemini_response` so `main.cpp` can grab it.

```cpp
#pragma once
#include <curl/curl.h>           // For sending HTTP POST requests to the Gemini API
#include <curl/easy.h>           // Extra curl helpers and options
#include <nlohmann/json_fwd.hpp> // Forward declarations for nlohmann/json (speeds up compile)
#include <iostream>              // For printing answers and errors to the console
#include <nlohmann/json.hpp>     // Full JSON library - build the request, parse the response
#include "Config.h"              // GEMINI_API_KEY lives here

class Brain {
public:
    // This string holds Gemini's response after askGemini() runs
    // main.cpp reads this to get the answer and pass it to VoiceOutput
    std::string gemini_response;

    // Convenient type alias - so we write json instead of nlohmann::json everywhere
    using json = nlohmann::json;

    // =========================================================
    // WRITE CALLBACK
    // libcurl calls this automatically every time it receives
    // a chunk of response data from the Gemini server.
    // We keep appending each chunk until we have the full response.
    // =========================================================
    static size_t writeCallback(void* contents,      // Raw pointer to the received data chunk
                                 size_t size,         // Size of each data unit (always 1 byte)
                                 size_t nmemb,        // Number of units in this chunk
                                 std::string* output) // The string where we collect all chunks
    {
        size_t totalSize = size * nmemb;              // Real byte count of this chunk
        output->append((char*)contents, totalSize);   // Append bytes to our string
        return totalSize;                             // Tell curl we handled all of it
    }

    // =========================================================
    // ASK GEMINI
    // Takes the user's transcribed text, sends it to Gemini,
    // and saves the AI's answer into gemini_response.
    // =========================================================
    void askGemini(const std::string& text) {

        // Create a new curl session handle
        CURL* curl = curl_easy_init();

        // If curl failed to initialize (very rare), just bail - nothing we can do
        if (!curl) return;

        // Which Gemini model to use - 2.5 Flash is fast and intelligent
        std::string model = "gemini-2.5-flash";

        // This string will collect the full HTTP response body from Gemini
        std::string response_string;

        // Build the full endpoint URL
        // We pass our API key as a query parameter at the end of the URL
        std::string url = "https://generativelanguage.googleapis.com/v1beta/models/"
                        + model
                        + ":generateContent?key="
                        + std::string(GEMINI_API_KEY);

        // Build the JSON request body in the exact format Gemini expects
        // We prepend a system prompt to make Gemini act like Jarvis
        // Then append the user's actual text question
        json requestBody = {
            {"contents", {{
                {"parts", {{
                    {"text", "You are Jarvis. Answer concisely, maintaining full context. Act as a helpful human-like assistant. " + text}
                }}}
            }}}
        };

        // Serialize the JSON object to a plain string - curl needs a C string to send
        std::string payloadStr = requestBody.dump();

        // Build the HTTP headers list
        // We must tell the server we're sending JSON in the body
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        // Configure the curl request options
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());              // Where to send the request
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payloadStr.c_str()); // What to send (JSON body)
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);           // Attach our headers
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);  // Function to collect response
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);   // Where to store the response

        try {
            // Fire the HTTP POST request - blocks until we get the complete response
            CURLcode res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                // Network level error - print the curl error message
                std::cerr << "curl failed: " << curl_easy_strerror(res) << std::endl;

            } else {
                // Parse the full JSON response string we collected
                json data = json::parse(response_string);

                // Check if the response has the "candidates" array we expect
                // Gemini always puts its answer inside candidates[0].content.parts[0].text
                if (data.contains("candidates")) {

                    // Navigate the nested JSON to extract the actual text answer
                    std::string answer = data["candidates"][0]["content"]["parts"][0]["text"].get<std::string>();

                    // Print the answer to the console so we can see it
                    std::cout << "Answer: " << answer << std::endl;

                    // Store the answer for main.cpp to read
                    gemini_response = answer;

                } else {
                    // Gemini returned something unexpected - could be a quota error or bad request
                    // Print the raw response so we can investigate
                    std::cerr << "Unexpected JSON: " << data.dump() << std::endl;
                }
            }

        } catch (const std::exception& e) {
            // Catch JSON parse errors or any other exceptions
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // Free the headers list we built - prevents memory leak
        curl_slist_free_all(headers);

        // Clean up and release this curl session
        curl_easy_cleanup(curl);
    }
};
```

---

<h1 align="center">VoiceOutput.h</h1>

This is the final step in the pipeline. It takes Gemini's text answer, sends it to the **ElevenLabs Text-to-Speech API** to generate a realistic human-sounding voice, saves the resulting audio as `output.mp3`, and plays it on Windows using the built-in MCI (Media Control Interface).

```cpp
#pragma once
#include <iostream>           // For printing status messages and errors
#include <curl/curl.h>        // For sending the HTTP request to ElevenLabs
#include <nlohmann/json.hpp>  // For building the JSON payload we send
#include "Config.h"           // ELEVEN_LABS_API_KEY and ELEVEN_LABS_VOICE_ID
#include <fstream>            // For writing the audio bytes to a .mp3 file on disk
#include <windows.h>          // For mciSendStringA - Windows audio playback

// =========================================================
// PLAY AUDIO FUNCTION
// Uses the Windows MCI API to open and play an mp3 file.
// MCI is part of Windows and needs no extra libraries.
// =========================================================
void playAudio(const std::string& filename) {
    // Open the mp3 file with MCI
    // "type mpegvideo" tells MCI this is an mp3/video file
    // "alias myAudio" gives it a short name for the next command
    mciSendStringA(("open \"" + filename + "\" type mpegvideo alias myAudio").c_str(), NULL, 0, NULL);

    // Start playing - this is non-blocking, audio plays in background
    // The rest of the program continues while the audio plays
    mciSendStringA("play myAudio", NULL, 0, NULL);
}

class VoiceOutput {
public:
    // Convenient type alias
    using json = nlohmann::json;

    // =========================================================
    // WRITE CALLBACK
    // libcurl calls this every time it receives a chunk of the
    // response from ElevenLabs. For audio responses, this is
    // raw binary bytes - not text! We collect all of it.
    // =========================================================
    static size_t WriteCallback(void* contents,      // Raw pointer to received data chunk
                                 size_t size,         // Size of each unit (always 1)
                                 size_t nmemb,        // Number of units in this chunk
                                 std::string* output) // Buffer where we accumulate all audio bytes
    {
        size_t totalSize = size * nmemb;              // Total bytes in this chunk
        output->append((char*)contents, totalSize);   // Append to our buffer
        return totalSize;                             // Tell curl we handled everything
    }

    // =========================================================
    // SPEAK
    // Takes a text string, sends it to ElevenLabs API,
    // receives audio bytes back, saves them as output.mp3,
    // and plays the file using the MCI audio API.
    // =========================================================
    void speak(const std::string& botResponse) {

        // The voice ID for ElevenLabs - "Rachel" voice
        // You can browse other voice IDs in your ElevenLabs dashboard
        std::string voiceId = "EXAVITQu4vr4xnSDxMaL";

        // Build the API URL - the voice ID is part of the endpoint path
        std::string url = "https://api.elevenlabs.io/v1/text-to-speech/" + voiceId;

        // Initialize curl globally before using it
        curl_global_init(CURL_GLOBAL_DEFAULT);

        // Create a new curl session for this request
        CURL* curl = curl_easy_init();

        CURLcode res;           // Will hold the result code of the curl request
        std::string readBuffer; // This will collect all the raw audio bytes from the API

        if (curl) {
            // Build the JSON request body that ElevenLabs expects
            json payload = {
                {"text", botResponse},                   // The text we want converted to speech
                {"model_id", "eleven_multilingual_v2"},  // TTS model - supports many languages well
                {"voice_settings", {
                    {"stability", 0.75},         // Voice consistency (0 = expressive, 1 = stable)
                    {"similarity_boost", 0.75}   // How closely it matches the original voice clone (0-1)
                }}
            };

            // Convert the JSON object to a string for the POST request body
            std::string jsonStr = payload.dump();

            // Build the HTTP headers
            struct curl_slist* headers = NULL;

            // ElevenLabs API key - required for authentication
            // Passed as a custom header "xi-api-key"
            headers = curl_slist_append(headers, ("xi-api-key: " + ELEVEN_LABS_API_KEY).c_str());

            // Tell ElevenLabs we're sending JSON in the request body
            headers = curl_slist_append(headers, "Content-Type: application/json");

            // Tell ElevenLabs we want to receive audio/mpeg (mp3) in the response
            headers = curl_slist_append(headers, "accept: audio/mpeg");

            // Set the callback to collect response bytes
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

            // Set the API endpoint URL
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

            // Attach our headers to the request
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            // Tell curl to put the response data into readBuffer
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

            // Set the JSON string as the POST body
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());

            // Make sure this is a POST request (not GET)
            curl_easy_setopt(curl, CURLOPT_POST, 1L);

            // Fire the request - blocks until ElevenLabs sends back the full audio
            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                // Network level failure
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;

            } else {
                // Check if ElevenLabs returned a JSON error response instead of audio
                // Real audio is binary data - if the response starts with {"detail": it's an API error
                if (readBuffer.find("{\"detail\":") != std::string::npos) {
                    std::cerr << "API Error: " << readBuffer << std::endl;

                } else {
                    // We got real audio bytes! Write them to output.mp3
                    // CRITICAL: std::ios::binary - audio is raw binary, not text characters
                    // Without this flag, Windows would corrupt the file during write
                    std::ofstream outFile("output.mp3", std::ios::binary);

                    if (outFile.is_open()) {
                        // Write all the collected audio bytes to the file
                        outFile.write(readBuffer.c_str(), readBuffer.size());

                        // Close the file - must be fully written before we try to play it
                        outFile.close();

                        std::cout << "Audio saved to output.mp3" << std::endl;

                        // Play the saved mp3 file using Windows MCI
                        // The :: prefix means we're calling the global playAudio() function
                        // (not a member function with the same name)
                        ::playAudio("output.mp3");

                    } else {
                        // File couldn't be opened - permissions issue or bad path
                        std::cerr << "Failed to open output file." << std::endl;
                    }
                }
            }
        }

        // Release all curl resources for this session
        curl_global_cleanup();
    }
};
```

---

<h1 align="center">Quick Tips I Learned Building This</h1>

> [!TIP]
> Always call `curl_global_init` once at the start of `main()` and `curl_global_cleanup` at the very end. Forgetting these causes weird memory issues especially on Windows.

> [!TIP]
> Vosk is very picky about sample rate. If you record at 44100 Hz but feed Vosk 16000 Hz - the transcription will be complete garbage. Make sure they always match.

> [!TIP]
> The `model/` folder for Vosk can be several hundred MB. Download the English small model from [alphacephei.com/vosk/models](https://alphacephei.com/vosk/models) and drop it right next to your `.exe`.

> [!WARNING]
> Never commit `Config.h` with real API keys to a public GitHub repo. Bots scan GitHub 24/7 looking for leaked keys. Add it to `.gitignore` immediately.

> [!WARNING]
> The `playAudio()` function using `mciSendStringA` is **non-blocking** - the program keeps running while audio plays. If Jarvis answers super fast and you hit Enter again, it'll cut off the current audio. Adding a wait for playback to finish would be a nice improvement.

> [!NOTE]
> Right now every message to Gemini is treated as a brand new conversation - there's no memory of what was said before. Adding a conversation history vector and passing previous messages each time would make Jarvis feel way more natural.

---

<h1 align="center">What I Want To Add Next</h1>

- [ ] **Conversation history** - pass previous messages to Gemini so it remembers context
- [ ] **Wake word detection** - say "Hey Jarvis" instead of pressing Enter every time
- [ ] **Wait for audio to finish** before looping back to recording
- [ ] **Linux / Mac support** - currently Windows-only because of WinMM for audio playback
- [ ] **Better error recovery** - if the API is down, retry instead of just skipping

---

<p align="center">
  <img src="https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png" width="100%" />
</p>

<p align="center">
  <b>Built from scratch by Denys</b><br>
  My most complex C++ project yet - a real working voice assistant • Learning step by step
</p>

<p align="center">
  Copyright © 2026
</p>
