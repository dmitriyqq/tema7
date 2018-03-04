cmake_minimum_required(VERSION 3.9)
project(7 C)

set(CMAKE_C_STANDARD 99)

add_executable(7
        main.c
        Database.h
        Database.c
        Datatypes.h
        Datatypes.c
        Utils.h
        Utils.c
        DebugFunctions.h
        DebugFunctions.c Functionality.h Functionality.c)