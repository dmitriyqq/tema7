cmake_minimum_required(VERSION 3.9)
project(7 C CXX)

set(CMAKE_C_STANDARD 99)

find_package(PkgConfig)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_subdirectory(Generator)

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
        View/View.h
        View/View.c View/Input.c View/Input.h Sort/Sort.c Sort/Sort.h BinTree/Tree.c BinTree/Tree.h LinkedList/LinkedList.c LinkedList/LinkedList.h)

