add_executable(usart_echo usart_echo.c)
target_include_directories(blinky PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(usart_echo usart)

include(../../tools/cmake/avr-utils.cmake)
generate_hex(usart_echo)
generate_dis(usart_echo)
generate_sym(usart_echo)

add_avrdude_target(usart_echo)
