cmake_minimum_required(VERSION 3.18)
project(tp4_git)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(tp4_git
        main.cpp
        PGM.cpp
        PGM.h
        PPM.cpp
        PPM.h)
