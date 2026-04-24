<p align="center">
  <img src="https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExeWowbXg5Mml1d213eThhdmNpMTlzbmxzZ3k1ODd1aHNlNzdhYjh4aiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/8nRxogx9tgvCzuSHLl/giphy.gif?raw=true" width="100%" alt="Jarvis Voice Assistant" />
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C++-Jarvis%20Voice%20Assistant-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
  <img src="https://img.shields.io/badge/Status-Working-success?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Voice-AI%20Assistant-blueviolet?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Features-Mic%20%2B%20Gemini%20%2B%20ElevenLabs-orange?style=for-the-badge" />
</p>

---

<h1 align="center">Jarvis_Final - My Own Voice Assistant</h1>

Yo guys!  
This is my biggest project ever! I made my own **Jarvis** like in Iron Man.  
You press Enter → speak into the mic → it listens → turns your voice into text with Vosk → sends it to Gemini AI → gets a smart answer → turns the answer into a cool voice with ElevenLabs → plays it out loud.  

I added **TONS AND TONS OF COMMENTS** — literally every single line, every variable, every function, every symbol, every action is explained super clearly.  
Even if I forget everything in a month, I can still understand what the hell is going on.

This is the full detailed README with **every single file fully commented**.

---

<h1 align="center">How Jarvis Works (Super Simple)</h1>

1. Waits for you to press Enter  
2. Records your voice with the microphone (miniaudio)  
3. Converts speech to text (Vosk)  
4. Sends the text to Gemini AI (the brain)  
5. Gets the answer back  
6. Sends the answer to ElevenLabs to make it speak  
7. Plays the MP3 file with Windows sound system  
8. Repeats forever until you close it

---

<h1 align="center">Project Structure</h1>

```
Jarvis_Final
├── include/                  ← All the header files with classes and functions
│   ├── Brain.h               ← The smart brain (Gemini API)
│   ├── Config.h              ← All secret API keys
│   ├── Recorder.h            ← Records audio from microphone
│   ├── Transcriber.h         ← Turns audio into text with Vosk
│   ├── VoiceOutput.h         ← Makes text speak with ElevenLabs + plays it
│   └── miniaudio.h           ← Huge audio library (included)
├── src/
│   └── main.cpp              ← The main program that runs everything
├── libs/vosk/                ← Vosk model and DLL files
├── CMakeLists.txt            ← Build instructions
└── README.md                 ← This file you're reading right now
```

---

<h1 align="center">Fully Commented Code (Every Line Explained)</h1>

### 1. Config.h
```cpp
#ifndef CONFIG_H          // This line prevents the file from being included more than once
#define CONFIG_H          // If the file is already included, skip everything below

#include <string>         // We need the string type to store our API keys

// These are constant strings that never change while the program runs
const std::string GEMINI_API_KEY = "AIzaSyBbRSmKqN-JznYD8TWUMomevB7OE31AQFY";
// This is my secret key from Google so Jarvis can talk to Gemini AI

const std::string ELEVEN_LABS_API_KEY = "sk_b4598f5c527049c701b56109bfbf7b3fccac899898e2cb01";
// This is my secret key from ElevenLabs so we can generate real human-like voice

const std::string ELEVEN_LABS_VOICE_ID = "EXAVITQu4vr4xnSDxMaL";
// This is the ID of the voice I like the most (calm male voice)

#endif // CONFIG_H        // End of the "include guard" so the file doesn't get duplicated
```

### 2. main.cpp (The main file that runs everything)
```cpp
#include <iostream>           // Allows us to print text to console and read from keyboard
#include <vector>             // We use this to store all the raw audio bytes we record
#include <string>             // We need strings to hold the text from user and from AI
#include "Config.h"           // Includes all our secret API keys
#include "Recorder.h"         // Header for recording microphone
#include "Transcriber.h"      // Header for turning audio into text
#include "Brain.h"            // Header for talking to Gemini AI
#include "VoiceOutput.h"      // Header for making the AI speak out loud

std::vector<char> fullRecording;   // This global vector will hold every single byte of audio we record from the mic

int main() {                       // This is where the program starts
    curl_global_init(CURL_GLOBAL_DEFAULT);   // We prepare the curl library once so we can use internet later

    Brain brain;                   // Create the Brain object (this is the part that talks to Gemini)
    VoiceOutput voiceOutput;       // Create the VoiceOutput object (this will make the AI speak)

    try {                          // We use try so if anything crashes we can catch the error
        while (true) {             // Infinite loop so Jarvis keeps listening forever until we close the program
            std::cout << "Hit Enter to start recording" << std::endl;   // Tell the user what to do
            std::cin.get();        // Wait for the user to press Enter (this clears the input buffer)

            fullRecording.clear();        // Delete any old recording so we start fresh
            startRecording();             // Call the function from Recorder.h to start listening to the mic

            if (fullRecording.empty()) {  // If nothing was recorded
                std::cout << "Recorn is empty, try again" << std::endl;   // Typo on purpose, it's funny
                continue;                 // Go back to the start of the loop
            }

            std::string userText = convertAudioToText(fullRecording);   // Call function from Transcriber.h

            if (userText.empty()) {       // If Vosk couldn't understand anything
                std::cout << "Enable to clealify text" << std::endl;   // Typo again, I know
                continue;
            }

            std::cout << "Вы: " << userText << std::endl;   // Show what the user said (in Russian because it's cool)

            brain.askGemini(userText);           // Send the text to Gemini AI
            std::string answer = brain.gemini_response;   // Get the answer back from the brain

            if (answer.empty()) {                 // If Gemini didn't give any answer
                std::cout << "I don't know" << std::endl;
                continue;
            }

            voiceOutput.speak(answer);            // Turn the answer into voice and play it

            std::cout << "Here we go." << std::endl;   // Just a fun message
        }
    } catch (const std::exception& e) {           // If something bad happens anywhere
        std::cerr << "Critical error: " << e.what() << std::endl;   // Print the error so I can fix it
    }

    curl_global_cleanup();   // Clean up curl before the program ends

    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();          // Wait for final Enter before closing
    return 0;                // Everything finished successfully
}
```

### 3. Recorder.h (Records audio from microphone)
```cpp
#pragma once                  // This makes sure the file is included only once
#include <iostream>           // For printing messages
#include <vector>             // To store audio bytes

#define MINIAUDIO_IMPLEMENTATION   // This tells miniaudio to include all its code
#include "miniaudio.h"        // The huge audio library that lets us use the microphone

extern std::vector<char> fullRecording;   // This is the same vector from main.cpp

// This function is called automatically by miniaudio every time the microphone gives us new sound data
void dataCallback(ma_device* device, void* output, const void* input, ma_uint32 frameCount) {
    if (input == NULL) return;   // If no input data, do nothing

    size_t bytesPerFrame = ma_get_bytes_per_frame(device->capture.format, device->capture.channels);
    // Calculate how many bytes each audio frame takes

    size_t bytesToCopy = frameCount * bytesPerFrame;   // How many bytes we got this time

    const char* inputData = (const char*)input;        // Turn the void pointer into something we can read
    fullRecording.insert(fullRecording.end(), inputData, inputData + bytesToCopy);  
    // Add the new audio bytes to our big vector
}

// This function starts the actual recording session
void startRecording() {
    ma_device_config deviceConfig = ma_device_config_init(ma_device_type_capture);  
    // Create a config for microphone (capture = listening)

    deviceConfig.capture.format = ma_format_s16;     // Use 16-bit audio (good quality)
    deviceConfig.capture.channels = 1;               // Mono = 1 channel
    deviceConfig.sampleRate = 16000;                 // 16000 Hz — exactly what Vosk needs
    deviceConfig.dataCallback = dataCallback;        // Tell miniaudio to call our function when data arrives

    ma_device device;                                // Create the device object
    if (ma_device_init(NULL, &deviceConfig, &device) == MA_SUCCESS) {   // Try to start the mic
        ma_device_start(&device);                    // Start listening
        std::cout << "Recording... Press Enter to stop." << std::endl;
        std::cin.get();                              // Wait for user to press Enter

        ma_device_stop(&device);                     // Stop recording
        ma_device_uninit(&device);                   // Clean up the device
    } else {
        std::cerr << "Failed to initialize capture device." << std::endl;
    }
}
```
