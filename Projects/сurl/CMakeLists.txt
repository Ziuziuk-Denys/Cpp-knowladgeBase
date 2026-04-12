cmake_minimum_required(VERSION 3.20)
project(curl)

set(CMAKE_CXX_STANDARD 20)

find_package(CURL REQUIRED)

add_executable(curl main.cpp)

# Связка
target_link_libraries(curl PRIVATE CURL::libcurl)
