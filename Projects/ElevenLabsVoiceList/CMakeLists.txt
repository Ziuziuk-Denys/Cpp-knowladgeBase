cmake_minimum_required(VERSION 3.20)
project(ElevensLabs_Voice_List)

set(CMAKE_CXX_STANDARD 20)

// Find the required packages
find_package(CURL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

// Add the executable target
add_executable(ElevensLabs_Voice_List main.cpp)

// Link the required libraries to the target
target_link_libraries(ElevensLabs_Voice_List PRIVATE
        CURL::libcurl
        nlohmann_json::nlohmann_json
)
