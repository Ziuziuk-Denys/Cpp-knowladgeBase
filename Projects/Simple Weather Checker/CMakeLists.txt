cmake_minimum_required(VERSION 4.1)
project(Voice_FIlter)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(Voice_FIlter main.cpp)
target_link_libraries(Voice_FIlter CURL::libcurl nlohmann_json::nlohmann_json)
