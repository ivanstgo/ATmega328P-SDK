#include "usart.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/**
 * Configures the USART0
 * @param mode USART mode
 * @param parity parity mode
 * @param stop_bit selects one o two stop bits
 * @param data_bits selects 5, 6, 7, 8 or 9 data bits
 * @param tx_rx enables receiver and transmitter
 * @param baud_rate sets baud rate
 */
void usart_init(char mode, char parity, char stop_bit, char data_bits, char tx_rx, unsigned long baud_rate)
{
    UCSR0A = 0;
    UCSR0B = 0;
    UCSR0C = 0;
    switch (mode)
    {
    case SYNCHRONOUS_MODE:
        UBRR0 = (unsigned int)((float)F_CPU / (baud_rate * 2.0f) - 1.0f);
        UCSR0C |= 1 << UMSEL00;
        break;
    case ASYNCHRONOUS_DOUBLE_SPEED_MODE:
        UCSR0A |= 1 << U2X0;
        UBRR0 = (unsigned int)((float)F_CPU / (baud_rate * 8.0f) - 1.0f);
        break;
    default:
        UBRR0 = (unsigned int)((float)F_CPU / (baud_rate * 16.0f) - 1.0f);
        break;
    }
    switch (parity)
    {
    case EVEN_PARITY:
        UCSR0C |= 1 << UPM01;
        break;
    case ODD_PARITY:
        UCSR0C |= (1 << UPM01) | (1 << UPM00);
        break;
    default:
        break;
    }
    switch (stop_bit)
    {
    case TWO_STOP_BIT:
        UCSR0C |= 1 << USBS0;
        break;
    default:
        break;
    }
    switch (data_bits)
    {
    case DATA_BITS_6:
        UCSR0C |= 1 << UCSZ00;
        break;
    case DATA_BITS_7:
        UCSR0C |= 1 << UCSZ01;
        break;
    case DATA_BITS_8:
        UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
        break;
    case DATA_BITS_9:
        UCSR0C |= (1 << UCSZ02) | (1 << UCSZ01) | (1 << UCSZ00);
        break;
    default:
        break;
    }
    switch (tx_rx)
    {
    case RECEIVER_ENABLE:
        UCSR0B |= 1 << RXEN0;
        break;
    case TRANSMITTER_ENABLE:
        UCSR0B |= 1 << TXEN0;
        break;
    default:
        UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
        break;
    }
}

/**
 * Receives a byte
 * @return the received byte
 */
unsigned char usart_receive(void)
{
    while ((UCSR0A & 0x80) == 0x00)
        ;
    return UDR0;
}

/**
 * Transmits one byte
 * @param data byte to be transmitted
 */
void usart_transmit(unsigned int data)
{
    while ((UCSR0A & 0x20) == 0x00)
        ;
    UDR0 = data;
}

/**
 * Transmits a string of characters
 * @param s string to be transmitted
 */
void usart_transmit_string(const char *s)
{
    int i = 0;
    while (*(s + i))
    {
        usart_transmit((unsigned int)*(s + i));
        i++;
    }
}