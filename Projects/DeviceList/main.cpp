#include <iostream>
#include <portaudio.h>

int main() {
    PaError error = Pa_Initialize();
    if (error != paNoError) {
        std::cout << "Pa_Initialize() failed: " << error << std::endl;
        return 1;
    }

    int numDevices = Pa_GetDeviceCount();
    if (numDevices <= 0) {
        std::cout << "Pa_GetDeviceCount() failed: " << numDevices << std::endl;
    } else {
        std::cout << "Pa_GetDeviceCount() succeeded: " << numDevices << std::endl;

        const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice());
        if (deviceInfo) {
            std::cout << "Pa_GetDeviceInfo() succeeded: " << deviceInfo->name << std::endl;
            std::cout << "Max Inputs : " << deviceInfo->maxInputChannels << std::endl;
        }
    }

    Pa_Terminate();
    return 0;
}
