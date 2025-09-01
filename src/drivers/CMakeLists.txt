set(SDK_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

add_library(io_pin STATIC io_pin.c)
target_include_directories(io_pin PUBLIC ${SDK_INCLUDE_PATH})

add_library(twi STATIC twi.c)
target_include_directories(twi PUBLIC ${SDK_INCLUDE_PATH})

add_library(usart_async STATIC usart_async.c)
target_include_directories(usart_async PUBLIC ${SDK_INCLUDE_PATH})
