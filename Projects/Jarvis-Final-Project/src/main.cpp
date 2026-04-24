#include <iostream>
#include <vector>
#include <string>
#include "Config.h"
#include "Recorder.h"
#include "Transcriber.h"
#include "Brain.h"
#include "VoiceOutput.h"

std::vector<char> fullRecording;

int main() {
    curl_global_init(CURL_GLOBAL_DEFAULT);

    Brain brain;
    VoiceOutput voiceOutput;


    try {
        while (true) {
            std::cout << "Hit Enter to start recording" << std::endl;
            std::cin.get();

            fullRecording.clear();
            startRecording();

            if (fullRecording.empty()) {
                std::cout << "Recorn is empty, try again" << std::endl;
                continue;
            }

            std::string userText = convertAudioToText(fullRecording);

            if (userText.empty()) {
                std::cout << "Enable to clealify text" << std::endl;
                continue;
            }
            std::cout << "You: " << userText << std::endl;

            brain.askGemini(userText);
            std::string answer = brain.gemini_response;

            if (answer.empty()) {
                std::cout << "Something went wrong" << std::endl;
                continue;
            }

            voiceOutput.speak(answer);

            std::cout << "Here we go." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Critical error: " << e.what() << std::endl;
    }

    curl_global_cleanup();

    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();
    return 0;
}
