# @file avr-toolchain.cmake
# @author Iván Santiago (https://github.com/ivanstgo)
# @date 04/07/2025 - 19:10
# @brief This file describes an AVR target platform and sets the avr-gnu-toolchain for cross-compiling

cmake_minimum_required(VERSION 3.30)

# The target processor is not running any operating system (bare-metal)
set(CMAKE_SYSTEM_NAME Generic)

# Set C compiler
set(CMAKE_C_COMPILER avr-gcc)
# Set assembler
set(CMAKE_ASM_COMPILER avr-as)
# Set C++ compiler
set(CMAKE_CXX_COMPILER avr-g++)

# Global C compiler flags
set(CMAKE_C_FLAGS_INIT "-mmcu=atmega328p")
