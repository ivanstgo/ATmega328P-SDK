add_executable(led_blink led_blink.c)
target_include_directories(led_blink PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(led_blink io_pin)


include(../../tools/cmake/avr-utils.cmake)
generate_hex(led_blink)
generate_dis(led_blink)
generate_sym(led_blink)

add_avrdude_target(led_blink)
