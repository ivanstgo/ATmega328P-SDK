add_executable(blinky blinky.c)
target_include_directories(blinky PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(blinky io_pin)

include(../../tools/cmake/avr-utils.cmake)
generate_hex(blinky)
generate_dis(blinky)
generate_sym(blinky)

add_avrdude_target(blinky)
