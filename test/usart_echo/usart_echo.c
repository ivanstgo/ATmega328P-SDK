/**
 * @brief This program tests the USART0 driver
 * by configuring it in asynchronous mode 8N1.
 * The received character is transmitted back after
 * transmitting the "Received: " string.
 * @author Iván Santiago
 * @date 16/07/25 - 22:26
 */
#include <avr/io.h>
#include <stdbool.h>
#include "usart.h"

int main(void)
{
    struct usart_config conf = {
        .a.flags = {
            .mpc_mode = false,
            .async_double_speed_mode = false
        },
        .b.flags = {
            .transmitter_enable = true,
            .receiver_enable = true,
            .data_register_empty_interrupt_enable = false,
            .tx_complete_interrupt_enable = false,
            .rx_complete_interrupt_enable = false
        },
        .c.flags = {
            .sync_clock_polarity = 0,
            .stop_bit_select = USART_STOP_1BIT,
            .parity_mode = USART_PARITY_DISABLED,
            .character_size = USART_CHAR_SIZE_8BIT,
            .mode_select = USART_ASYNCHRONOUS
        }
    };
    usart_configure(conf, 9600u);
    char msg[] = "Received: ";
    while(1)
    {
        char received = usart_receive();
        usart_transmit_string(msg);
        usart_transmit(received);
        usart_transmit('\r');
    }
    return 0;
}
