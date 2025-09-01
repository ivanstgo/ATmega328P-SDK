/**
 * @file usart_async.h
 * @author Iván Santiago (https://github.com/ivanstgo)
 * @date 31/08/2025 - 14:37
 * @brief Driver for ATmega328p USART0 in asyncrhonous mode.
 */

#ifndef __USART_ASYNC_H
#define __USART_ASYNC_H

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

/**
 * @brief Macro to get the value of the flags that indicate if there were errors
 * when receiving a byte.
 */
#define USART_RX_ERROR (UCSR0A & (_BV(UPE0) | (_BV(DOR0) | _BV(FE0))))

/**
 * @brief Number of data bits.
 */
enum usart_character_size
{
    USART_5_BITS,
    USART_6_BITS = _BV(UCSZ00),
    USART_7_BITS = _BV(UCSZ01),
    USART_8_BITS = _BV(UCSZ00) | _BV(UCSZ01)
};

/**
 * @brief Number of stop bits.
 */
enum usart_stop_bits
{
    USART_ONE_STOP_BIT,
    USART_TWO_STOP_BITS = _BV(USBS0)
};

/**
 * @brief Parity mode.
 */
enum usart_parity_mode
{
    USART_NO_PARITY,
    USART_EVEN_PARITY = _BV(UPM01),
    USART_ODD_PARITY = _BV(UPM00) | _BV(UPM01)
};

/**
 * @brief USART configuration struct. It indicates frame format and if the
 * transmitter and receiver are enabled.
 */
struct usart_async_config
{
    enum usart_character_size size;
    enum usart_stop_bits stop_bits;
    enum usart_parity_mode parity;
    bool enable_tx;
    bool enable_rx;
};

/**
 * @brief Transmits one byte.
 * @param data Byte to be transmitted.
 */
static inline void usart_transmit(uint8_t data)
{
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data;
}

static inline uint8_t usart_receive(void)
{
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}

/**
 * @brief Configures USART0 to operate in asynchronous mode.
 * @param config Configuration struct.
 * @param baud_rate Baud rate.
 */
void usart_async_configure(struct usart_async_config config, uint32_t baudrate);

/**
 * @brief Writes data to the tx buffer.
 * @param src Pointer to data source.
 * @param length Number of bytes to write.
 * @return Number of successfully written bytes.
 */
void usart_async_write(uint8_t *src, uint16_t length);

/**
 * @brief Reads data from the rx buffer.
 * @param dst Pointer to data destination.
 * @param length Number of bytes to read.
 * @return Number of successfully read bytes.
 */
uint16_t usart_async_read(uint8_t *dst, uint16_t length);

/**
 * @brief Transmits a zero-terminated string.
 * @param str String.
 */
void usart_async_put_string(const char * str);

#endif /* !__USART_ASYNC_H */
