add_executable(scanner i2c_scanner.c)
target_include_directories(scanner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(scanner twi usart_async io_pin)


include(../../tools/cmake/avr-utils.cmake)
generate_hex(scanner)
generate_dis(scanner)
generate_sym(scanner)

add_avrdude_target(scanner)
