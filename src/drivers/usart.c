/**
 * @file usart.c
 * @author Iván Santiago (gh: ivanstgo)
 * @date 26/08/2025 - 15:23
 * @brief ATmega328P USART driver implementation.
 */

#include "drivers/usart.h"

/**
 * @brief Macro to mask the value of the parity error, frame error and data
 * overrun flags.
 */
#define USART_RX_FLAGS_MASK ((1u << UPE0) |  (1u << DOR0) | (1u << FE0))

void usart_configure(struct usart_config config, uint32_t baud_rate)
{
    UCSR0A = (config.double_speed_mode << U2X0) | (config.mpc_mode << MPCM0);
    UCSR0B = (config.enable_transmitter << TXEN0) |
             (config.enable_receiver << RXEN0);
    UCSR0C = config.clock_polarity | config.character_size | config.stop_bits |
             config.parity_mode | config.mode;
    uint32_t br = 0;
    if (config.mode == USART_ASYNCHRONOUS)
    {
        if (config.double_speed_mode)
        {
            br = (F_CPU / (baud_rate << 3u)) - 1;
        }
        else
        {
            br = (F_CPU / (baud_rate << 4u)) - 1;
        }
    }
    else
    {
        br = (F_CPU / (baud_rate << 1u)) - 1;
    }
    UBRR0 = (uint16_t)br;
}

uint16_t usart_write(uint8_t *src, uint16_t length)
{
    uint16_t i = 0;
    for (i = 0; i < length; i++)
    {
        usart_transmit(src[i]);
    }
    return i;
}

uint16_t usart_read(uint8_t *dst, uint16_t length)
{
    uint16_t i = 0;
    for (i = 0; i < length; i++)
    {
        dst[i] = usart_receive();
        if (UCSR0A & USART_RX_FLAGS_MASK) break;
    }
    return i;
}
