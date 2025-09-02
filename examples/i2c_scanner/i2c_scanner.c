/**
 * @file i2c_scanner.c
 * @author Iván Santiago (https://github.com/ivanstgo)
 * @date 01/09/2025 - 22:47
 * @brief This program probes each slave address and prints out scanning results
 * through USART0.
 */

#include "drivers/io_pin.h"
#include "drivers/usart_async.h"
#include "drivers/twi.h"

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
    struct usart_async_config usart_config = {
        .size = USART_8_BITS,
        .stop_bits = USART_ONE_STOP_BIT,
        .parity = USART_NO_PARITY,
        .enable_tx = true,
        .enable_rx = true
    };
    usart_async_configure(usart_config, 9600);
    
    // Configure 2-Wire serial interface
    twi_configure(100000);
 
    while (true)
    {
        usart_async_put_string("Do you want to start a bus scan? [y/n]\n");
        
        while (usart_receive() != 'y')
        {
            usart_async_put_string("Do you want to start a bus scan? [y/n]\n");
        }
        bool results[128];
        for (uint16_t i = 0; i < 128; i++)
        {
            twi_start();
            twi_transmit(TWI_SLA_READ(i));
            results[i] = TW_STATUS == TW_MR_SLA_ACK;
        }
        twi_stop();
        char buffer[] = "   00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n";
        usart_async_put_string(buffer);
        for (uint16_t i = 0; i < 8; i++)
        {
            buffer[0] = '0' + i;
            buffer[1] = '0';
            buffer[2] = ' ';
            uint16_t buffer_index = 3;
            for (uint16_t j = 0; j < 16; j++)
            {
                if (results[j | (i << 4)])
                {
                    buffer[buffer_index] = '0' + i;
                    buffer[buffer_index + 1] = j < 10 ? '0' + j : 'A' + j - 10;
                    buffer[buffer_index + 2] = ' ';
                }
                else
                {
                    buffer[buffer_index] = '-';
                    buffer[buffer_index + 1] = ' ';
                    buffer[buffer_index + 2] = ' ';
                }
                buffer_index += 3;
            }
            buffer[buffer_index] = '\n';
            usart_async_put_string(buffer);
        }
    }
    return 0;
}
