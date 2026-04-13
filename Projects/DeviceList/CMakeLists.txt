#JUST EXAMPLE
cmake_minimum_required(VERSION 3.20)
project(Final_Project)

set(CMAKE_CXX_STANDARD 20)

find_package(PortAudio CONFIG REQUIRED)

add_executable(Final_Project main.cpp)

target_link_libraries(Final_Project PRIVATE portaudio)
