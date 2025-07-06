add_library(adc STATIC adc.c adc.h)
target_include_directories(adc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
