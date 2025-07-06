add_library(ssd1306 STATIC ssd1306.c ssd1306.h graphics.c graphics.h)
# SSD1306 library depends on I2C driver
target_link_libraries(ssd1306 i2c)
target_include_directories(ssd1306 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
