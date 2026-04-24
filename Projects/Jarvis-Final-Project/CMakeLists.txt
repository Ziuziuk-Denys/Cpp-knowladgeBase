#IT'S JUST AN EXAMPLE OF CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(Jarvis_Final)

set(CMAKE_CXX_STANDARD 20)

find_package(CURL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

set(VOSK_DIR "${CMAKE_SOURCE_DIR}/libs/vosk")
find_path(VOSK_INCLUDE_DIR NAMES vosk_api.h PATHS ${VOSK_DIR} NO_DEFAULT_PATH)
find_library(VOSK_LIBRARY NAMES vosk PATHS ${VOSK_DIR} NO_DEFAULT_PATH)

add_executable(Jarvis
        src/main.cpp
        include/Config.h
        include/Recorder.h
        include/Transcriber.h
        include/Brain.h
        include/VoiceOutput.h
)

target_include_directories(Jarvis PRIVATE include ${VOSK_INCLUDE_DIR})
target_link_libraries(Jarvis PRIVATE
        CURL::libcurl
        nlohmann_json::nlohmann_json
        ${VOSK_LIBRARY}
        winmm.lib
)

add_custom_command(TARGET Jarvis POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${VOSK_DIR}/vosk.dll" "$<TARGET_FILE_DIR:Jarvis>/libvosk.dll"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${VOSK_DIR}/libgcc_s_seh-1.dll" "$<TARGET_FILE_DIR:Jarvis>/libgcc_s_seh-1.dll"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${VOSK_DIR}/libstdc++-6.dll" "$<TARGET_FILE_DIR:Jarvis>/libstdc++-6.dll"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${VOSK_DIR}/libwinpthread-1.dll" "$<TARGET_FILE_DIR:Jarvis>/libwinpthread-1.dll"
)
