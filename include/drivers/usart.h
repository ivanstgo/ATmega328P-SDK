/**
 * @file usart.h
 * @author Iván Santiago
 * @date 26/08/2025 - 13:25
 * @brief ATmega328P USART driver.
 */

#ifndef __USART_H
#define __USART_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

/**
 * @brief Macro to wait until the USART data register_empty flag is set.
 */
#define USART_WAIT_DATA_REGISTER_EMPTY_FLAG while(!(UCSR0A & (1u << UDRE0)))

/**
 * @brief Macro to wait until the USART receive complete flag is set.
 */
#define USART_WAIT_RECEIVE_COMPLETE_FLAG while (!(UCSR0A & (1u << RXC0)))

/**
 * @brief Macro to wait until the USART transmit complete flag is set.
 */
#define USART_WAIT_TRANSMIT_COMPLETE_FLAG while (!(UCSR0A & (1u << TXC0)))

/**
 * @brief Clock polarity when USART operates in synchronous mode.
 */
enum usart_sync_clock_polarity
{
    USART_CLK_ASYNC_OPERATION, USART_TRANSMIT_ON_RISING_EDGE = 0,
    USART_TRANSMIT_ON_FALLING_EDGE = 1u << UCPOL0
};

/**
 * @brief USART character size.
 */
enum usart_character_size
{
    USART_CHARACTER_5BIT,
    USART_CHARACTER_6BIT = 1u << UCSZ00,
    USART_CHARACTER_7BIT = 1u << UCSZ01,
    USART_CHARACTER_8BIT = (1u << UCSZ00) | (1u << UCSZ01),
};

/**
 * @brief Number of stop bits.
 */
enum usart_stop_bits
{
    USART_STOP_1BIT,
    USART_STOP_2BIT = 1u << USBS0
};

/**
 * @brief USART parity mode.
 */
enum usart_parity_mode
{
    USART_PARITY_DISABLED,
    USART_EVEN_PARITY = 1u << UPM01,
    USART_ODD_PARITY = (1u << UPM00) | (1u << UPM01)
};

/**
 * @brief USART mode of operation.
 */
enum usart_mode
{
    USART_ASYNCHRONOUS,
    USART_SYNCRHONOUS = 1u << UMSEL00,
    USART_MASTER_SPI = (1u << UMSEL00) | (1u << UMSEL01)
};

/**
 * @brief This structure is used to configure the USART0.
 */
struct usart_config
{
    uint8_t mode;
    uint8_t parity_mode;
    uint8_t stop_bits;
    uint8_t character_size;
    uint8_t clock_polarity;
    bool enable_transmitter;
    bool enable_receiver;
    bool double_speed_mode;
    bool mpc_mode;
};

/**
 * @brief Transmits one byte.
 * @param data Byte to be transmitted.
 */
static inline void usart_transmit(uint8_t data)
{
    USART_WAIT_DATA_REGISTER_EMPTY_FLAG;
    UDR0 = data;
}

/**
 * @brief Receives one byte.
 * @return Received byte.
 */
static uint8_t usart_receive(void)
{
    USART_WAIT_RECEIVE_COMPLETE_FLAG;
    return UDR0;
}

/**
 * @brief Configures the USART using a usart_config struct.
 * @param config USART configuration.
 * @param baud_rate Target baudrate (e.g. 9600)
 */
void usart_configure(struct usart_config config, uint32_t baud_rate);

/**
 * @brief Writes some bytes.
 * @param src Pointer to data source.
 * @param length Number of bytes write.
 * @return Number of successfully written bytes.
 */
uint16_t usart_write(uint8_t *src, uint16_t length);

/**
 * @brief Reads some bytes.
 * @param dst Pointer to data destination.
 * @param length Number of bytes to receive.
 * @return Number of successfully read bytes.
 */
uint16_t usart_read(uint8_t *dst, uint16_t length);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !__USART_H */
