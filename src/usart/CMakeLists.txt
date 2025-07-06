add_library(usart STATIC usart.c usart.h)
target_include_directories(usart PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
