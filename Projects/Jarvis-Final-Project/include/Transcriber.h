#pragma once
#include <vosk_api.h>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>

std::string convertAudioToText(std::vector<char> fullRecording){
    std::string text;

    std::cout << "Recording size: " << fullRecording.size() << " bytes" << std::endl;

    VoskModel* model = vosk_model_new("model");

    VoskRecognizer* recognizer = vosk_recognizer_new(model, 16000.0);

    int completed = vosk_recognizer_accept_waveform(recognizer, fullRecording.data(), fullRecording.size());

    const char* result;
    if (completed) {
        result = vosk_recognizer_result(recognizer);
    } else {
        result = vosk_recognizer_final_result(recognizer);
    }

    std::cout << "Recognized JSON: " << result << std::endl;

    // Parse the JSON to extract just the text
    nlohmann::json jsonData = nlohmann::json::parse(result);
    if (jsonData.contains("text")) {
        text = jsonData["text"].get<std::string>();
    } else {
        text = result; // Fallback
    }

    vosk_recognizer_free(recognizer);
    vosk_model_free(model);

    return text;
}
