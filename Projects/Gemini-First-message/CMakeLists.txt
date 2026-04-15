# JUST EXAMPLE 
cmake_minimum_required(VERSION 3.20)
project(Gemini)

set(CMAKE_CXX_STANDARD 20)

find_package(CURL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(Gemini main.cpp config.h)

target_link_libraries(Gemini PRIVATE
        CURL::libcurl
        nlohmann_json::nlohmann_json
)
