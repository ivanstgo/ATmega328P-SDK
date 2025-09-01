/**
 * @file usart_async.c
 * @author Iván Santiago (https://github.com/ivanstgo)
 * @date 31/08/2025 - 14:37
 * @brief Driver to use ATmega328p USART0 in asyncrhonous mode.
 */

#include "drivers/usart_async.h"

#ifndef F_CPU
#define F_CPU 16000000ul
#warning "Using F_CPU=16000000ul for baud rate calculation as it has not been defined."
#endif /* !F_CPU */

void usart_async_configure(struct usart_async_config config, uint32_t baudrate)
{
    UCSR0A = 0;
    UCSR0B = (config.enable_tx << TXEN0) | (config.enable_rx << RXEN0);
    UCSR0C = config.size | config.stop_bits | config.parity;

    uint32_t br = (F_CPU / (16 * baudrate)) - 1;
    UBRR0 = (uint16_t)br;
}

void usart_async_write(uint8_t *src, uint16_t length)
{
    for (uint16_t i = 0; i < length; i++) usart_transmit(*(src + i));
}

uint16_t usart_async_read(uint8_t *dst, uint16_t length)
{
    uint16_t i = 0;
    for (i = 0; i < length; i++)
    {
        *(dst + i) = usart_receive();
        if (USART_RX_ERROR) break;
    }
    return i;
}

void usart_async_put_string(const char * str)
{
    uint16_t i = 0;
    while (*(str + i)) usart_transmit(*(str + i++));
}
