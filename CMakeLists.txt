cmake_minimum_required(VERSION 3.26)
project(Pokemon_Battles)

set(CMAKE_CXX_STANDARD 17)

add_executable(Pokemon_Battles main.cpp
        Pokemon.cpp
        Pokemon.h
)
