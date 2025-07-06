# @file avr-binutils.cmake @author Iván Santiago (gh: ivanstgo) @date 04/07/2025
# - 19:29 @brief This file contains functions to get additional output files

cmake_minimum_required(VERSION 3.30)

# @brief Extracts the binary executable from a .elf file into a .hex file
# @param TARGET target
function(generate_hex TARGET)
  add_custom_command(
    TARGET ${TARGET}
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex -R .eeprom ${TARGET} ${TARGET}.hex
    VERBATIM)
endfunction()

# @brief Gets the assembly code from an executable .elf file
# @param TARGET target
function(generate_dis TARGET)
  add_custom_command(
    TARGET ${TARGET}
    POST_BUILD
    COMMAND ${CMAKE_OBJDUMP} -h -S ${TARGET} > ${TARGET}.dis
    VERBATIM)
endfunction()

# @brief Gets a list of symbols from a .elf file
# @param TARGET target
function(generate_sym TARGET)
  add_custom_command(
    TARGET ${TARGET}
    POST_BUILD
    COMMAND ${CMAKE_NM} -n ${TARGET} > ${TARGET}.sym
    VERBATIM)
endfunction()

# @brief Adds a custom target to flash the microcontroller using avrdude
# @param TARGET target
function(add_avrdude_target TARGET)
  add_custom_target(
    flash_${TARGET}
    DEPENDS ${TARGET}.hex
    COMMAND avrdude -p atmega328p -P /dev/ttyACM0 -c arduino -v -U
            flash:w:${TARGET}.hex)
endfunction()
