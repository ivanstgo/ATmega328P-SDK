add_library(io_pin STATIC io_pin.c io_pin.h)
target_include_directories(io_pin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})