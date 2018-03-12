cmake_minimum_required(VERSION 3.8)

set(PROJECT_NAME Generator)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(gen main.cpp)