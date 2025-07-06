/**
 * @file usart.h
 * @author Iván Santiago
 * @date 07-01-2023 18:09
 * @brief Library for using ATmega328P USART0
*/
#ifndef _USART_H_
#define _USART_H_
#define NO_PARITY 'N'
#define EVEN_PARITY 'E'
#define ODD_PARITY 'O'
#define ASYNCHRONOUS_MODE 'A'
#define ASYNCHRONOUS_DOUBLE_SPEED_MODE 'D'
#define SYNCHRONOUS_MODE 'S'
#define MASTER_SPI_MODE 'M'
#define ONE_STOP_BIT '1'
#define TWO_STOP_BIT '2'
#define DATA_BITS_5 '5'
#define DATA_BITS_6 '6'
#define DATA_BITS_7 '7'
#define DATA_BITS_8 '8'
#define DATA_BITS_9 '9'
#define RECEIVER_ENABLE 'R'
#define TRANSMITTER_ENABLE 'T'
#define TRANSCEIVER_ENABLE 'B'

/**
 * Stores the received byte
*/
volatile unsigned char usart_received_char;
/**
 * Configures the USART0
 * @param mode USART mode
 * @param parity parity mode
 * @param stop_bit selects one o two stop bits
 * @param data_bits selects 5, 6, 7, 8 or 9 data bits
 * @param tx_rx enables receiver and transmitter
 * @param baud_rate sets baud rate
 */
void usart_init(char mode, char parity, char stop_bit, char data_bits, char tx_rx, unsigned long baud_rate);
/**
 * Transmits one byte
 * @param data byte to be transmitted
 */
void usart_transmit(unsigned int data);
/**
 * Transmits a string of characters
 * @param s string to be transmitted
 */
void usart_transmit_string(const char *s);
/**
 * Receives a byte
 * @return the received byte
 */
unsigned char usart_receive(void);
#endif