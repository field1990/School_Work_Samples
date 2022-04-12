cmake_minimum_required(VERSION 3.17)
project(Assignment_3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(Assignment_3
        src/main.cpp src/binarysearchtree.cpp src/binarysearchtree.h src/spell_checker.cpp src/spell_checker.h)