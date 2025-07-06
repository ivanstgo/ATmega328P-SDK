add_library(i2c STATIC i2c.c i2c.h)
target_include_directories(i2c PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
