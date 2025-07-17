#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>
#include "usart.h"

static volatile union usart_ctrl_register_a *usart_reg_a = (union usart_ctrl_register_a *)&UCSR0A;
static volatile union usart_ctrl_register_b *usart_reg_b = (union usart_ctrl_register_b *)&UCSR0B;
static volatile union usart_ctrl_register_c *usart_reg_c = (union usart_ctrl_register_c *)&UCSR0C;

void usart_configure(struct usart_config config, uint32_t baudrate)
{
    usart_reg_a->reg = config.a.reg;
    usart_reg_b->reg = config.b.reg;
    usart_reg_c->reg = config.c.reg;

    uint32_t br = 0;

    if (config.c.flags.mode_select == USART_ASYNCHRONOUS)
    {
        if (config.a.flags.async_double_speed_mode)
        {
            br = (F_CPU / (baudrate << 3u)) - 1;
        }
        else
        {
            br = (F_CPU / (baudrate << 4u)) - 1;
        }
    }
    else
    {
        br = (F_CPU / (baudrate << 1u)) - 1; 
    }
    UBRR0 = (uint16_t)br;
}

void usart_transmit(uint8_t data)
{
    // Wait until data register empty flag is set
    while (!usart_reg_a->flags.data_register_empty);
    UDR0 = data;
}

uint8_t usart_receive(void)
{
    // Wait until receive complete flag is set
    while (!usart_reg_a->flags.receive_complete);
    return UDR0;
}

void usart_transmit_string(char *str)
{
    uint16_t i = 0;
    while (*(str + i))
    {
        usart_transmit(*(str + i));
        i++;
    }
}
