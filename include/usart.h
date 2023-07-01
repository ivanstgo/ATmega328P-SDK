#ifndef USART_H_
#define USART_H_
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

volatile unsigned char usart_received_char;
void usart_init(char mode, char parity, char stop_bit, char data_bits, char tx_rx, unsigned long baud_rate);
void usart_transmit(unsigned int data);
void usart_transmit_string(const char *s);
unsigned char usart_receive(void);
#endif