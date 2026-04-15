# IT'S ONLY AN EXAMPLE. CMake files are always based on your file names and paths to files on your PC.
cmake_minimum_required(VERSION 3.20)
project(ElevensLabs_Voice_List___copy)

set(CMAKE_CXX_STANDARD 20)


find_package(CURL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)


add_executable(ElevensLabs_Voice_List___copy main.cpp)


target_link_libraries(ElevensLabs_Voice_List___copy PRIVATE
        CURL::libcurl
        nlohmann_json::nlohmann_json
)
