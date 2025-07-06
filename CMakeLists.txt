cmake_minimum_required(VERSION 3.30)

project(ATmega328P-sdk C CXX ASM)

add_definitions(-DF_CPU=16000000ul)

add_subdirectory(./src/)
add_subdirectory(./test/)
