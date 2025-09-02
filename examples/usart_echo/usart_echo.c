/**
 * @file usart_echo.c
 * @author Iván Santiago (https://github.com/ivanstgo)
 * @date 25/08/2025 - 18:44
 * @brief This example program configures the USART0 in asynchronous mode
 * 8N1@9600 and transmits back the content of a buffer after filling it with
 * received data.
 */
#include <util/delay.h>
#include "drivers/usart_async.h"
#include "drivers/io_pin.h"

#define BAUD_RATE 9600
#define BUFFER_SIZE 4

int main(void)
{
    // Configure RX pin
    struct pin_config rx_pin = {
        .pin = PIN_RXD,
        .dir = INPUT,
        .pull_up = PULL_UP_DISABLED,
        .value = LOW
    };
    pin_configure(rx_pin);

    // Configure TX pin
    struct pin_config tx_pin = {
        .pin = PIN_TXD,
        .dir = OUTPUT,
        .pull_up = PULL_UP_DISABLED,
        .value = HIGH
    };
    pin_configure(tx_pin);

    // Configure USART
    struct usart_async_config config = {
        .size = USART_8_BITS,
        .stop_bits = USART_ONE_STOP_BIT,
        .parity = USART_NO_PARITY,
        .enable_tx = true,
        .enable_rx = true
    };
    usart_async_configure(config, BAUD_RATE);
    
    uint8_t buffer[BUFFER_SIZE];
    uint16_t received = 0;
    usart_async_put_string("Using USART0 in asynchronous mode.");
    while(1)
    {
        received = usart_async_read(buffer, BUFFER_SIZE);
        usart_async_write(buffer, received);
    }
    return 0;
}
