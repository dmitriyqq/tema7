cmake_minimum_required(VERSION 3.9)
project(kursovaya)

set(CMAKE_CXX_STANDARD 11)

add_executable(kursovaya main.cpp stuff.h stuff.cpp)

add_executable(bot bot.cpp stuff.cpp stuff.h)