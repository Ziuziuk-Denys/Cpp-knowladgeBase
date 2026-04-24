#pragma once
#include <iostream>
#include <vector>

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

extern std::vector<char> fullRecording;

void dataCallback(ma_device* device, void* output, const void* input, ma_uint32 frameCount) {
    if (input == NULL) return;

    size_t bytesPerFrame = ma_get_bytes_per_frame(device->capture.format, device->capture.channels);
    size_t bytesToCopy = frameCount * bytesPerFrame;

    const char* inputData = (const char*)input;
    fullRecording.insert(fullRecording.end(), inputData, inputData + bytesToCopy);
}

void startRecording() {
    ma_device_config deviceConfig = ma_device_config_init(ma_device_type_capture);
    deviceConfig.capture.format = ma_format_s16;
    deviceConfig.capture.channels = 1;
    deviceConfig.sampleRate = 16000;
    deviceConfig.dataCallback = dataCallback;

    ma_device device;
    if (ma_device_init(NULL, &deviceConfig, &device) == MA_SUCCESS) {
        ma_device_start(&device);
        std::cout << "Recording... Press Enter to stop." << std::endl;
        std::cin.get();

        ma_device_stop(&device);
        ma_device_uninit(&device);
    } else {
        std::cerr << "Failed to initialize capture device." << std::endl;
    }
}
