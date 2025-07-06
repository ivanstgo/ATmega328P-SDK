add_library(timers STATIC timers.c timers.h)
target_include_directories(timers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
