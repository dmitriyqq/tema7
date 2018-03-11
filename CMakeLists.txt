cmake_minimum_required(VERSION 3.9)
project(7 C)

set(CMAKE_C_STANDARD 99)

find_package(PkgConfig)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(7
        main.c
        Database/Database.h
        Database/Database.c
        Model/Datatypes.h
        Model/Datatypes.c
        Database/Utils.h
        Database/Utils.c
        View/DebugFunctions.h
        View/DebugFunctions.c
        View/InputFunctions.h
        View/InputFunctions.c
        View/View.h
        View/View.c)
