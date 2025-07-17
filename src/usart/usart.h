/**
 * @file usart.h
 * @author Iván Santiago
 * @date 07-01-2023 18:09
 * @brief Library for using ATmega328P USART0
*/
#ifndef USART_H_
#define USART_H_

#include <stdint.h>

/**
 * @brief USART synchronous clock polarity
 */
enum usart_sync_clk_polarity
{
    USART_TX_RISING_RX_FALLING,
    USART_TX_FALLING_RX_RISING
};

/**
 * @brief USART character size
 */
enum usart_character_size
{
    USART_CHAR_SIZE_5BIT,
    USART_CHAR_SIZE_6BIT,
    USART_CHAR_SIZE_7BIT,
    USART_CHAR_SIZE_8BIT
};

/**
 * @brief USART asynchronous transmitter stop bit number
 */
enum usart_stop_bit_select
{
    USART_STOP_1BIT,
    USART_STOP_2BIT
};

/**
 * @brief USART parity modes
 */
enum usart_parity_mode
{
    USART_PARITY_DISABLED,
    USART_EVEN_PARITY = 2,
    USART_ODD_PARITY
};

/**
 * @brief USART modes
 */
enum usart_mode_select
{
    USART_ASYNCHRONOUS,
    USART_SYNCHRONOUS,
    USART_MASTER_SPI = 3
};

/**
 * @brief USART0 control and status register A
 */
union usart_ctrl_register_a
{
    uint8_t reg;
    struct
    {
        uint8_t mpc_mode : 1;
        uint8_t async_double_speed_mode : 1;
        uint8_t parity_error : 1;
        uint8_t data_overrun : 1;
        uint8_t frame_error : 1;
        uint8_t data_register_empty : 1;
        uint8_t transmit_complete : 1;
        uint8_t receive_complete : 1;
    } flags;
};

/**
 * @brief USART0 control and status register B
 */
union usart_ctrl_register_b
{
    uint8_t reg;
    struct
    {
        uint8_t transmit_data_bit8 : 1;
        uint8_t receive_data_bit8 : 1;
        uint8_t char_size_n2 : 1;
        uint8_t transmitter_enable : 1;
        uint8_t receiver_enable : 1;
        uint8_t data_register_empty_interrupt_enable : 1;
        uint8_t tx_complete_interrupt_enable : 1;
        uint8_t rx_complete_interrupt_enable : 1;
    } flags;
};

/**
 * @brief USART0 control and status register C
 */
union usart_ctrl_register_c
{
    uint8_t reg;
    struct
    {
        uint8_t sync_clock_polarity : 1;
        uint8_t character_size : 2;
        uint8_t stop_bit_select : 1;
        uint8_t parity_mode : 2;
        uint8_t mode_select : 2;
    } flags;
};

/**
 * @brief USART0 configuration struct
 */
struct usart_config
{
    union usart_ctrl_register_a a;
    union usart_ctrl_register_b b;
    union usart_ctrl_register_c c;
};

/**
 * @brief Configures the USART0 using a usart_config struct
 * @param config USART configuration
 * @param baudrate target baudrate in Hz (e.g. 9600u)
 */
void usart_configure(struct usart_config config, uint32_t baudrate);

/**
 * @brief Transmits one character
 * @param data character to be transmitted
 */
void usart_transmit(uint8_t data);

/**
 * Receives one character
 * @return received data
 */
uint8_t usart_receive(void);

/**
 * @brief Transmits a zero terminated string
 * @param str string
 */
void usart_transmit_string(char *str);

#endif /* !USART_H_ */
