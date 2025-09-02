add_executable(usart_echo usart_echo.c)
target_include_directories(usart_echo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(usart_echo io_pin usart_async)


include(../../tools/cmake/avr-utils.cmake)
generate_hex(usart_echo)
generate_dis(usart_echo)
generate_sym(usart_echo)

add_avrdude_target(usart_echo)
