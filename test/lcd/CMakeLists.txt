add_executable(lcd lcd.c)
target_include_directories(lcd PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(lcd io_pin hd44780)

include(../../tools/cmake/avr-utils.cmake)
generate_hex(lcd)
generate_dis(lcd)
generate_sym(lcd)

add_avrdude_target(lcd)
