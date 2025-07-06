add_library(hd44780 STATIC hd44780.c hd44780.h)
# HD44780 library depends on I2C driver
target_link_libraries(hd44780 i2c)
target_include_directories(hd44780 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
