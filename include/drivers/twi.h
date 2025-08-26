/**
 * @file twi.c
 * @author Iván Santiago (gh: ivanstgo)
 * @date 25/08/2025 - 20:04
 * @brief ATmega328P 2-wire serial interface driver.
 */

#ifndef __TWI_H
#define __TWI_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <avr/io.h>
#include <util/twi.h>

/**
 * @brief Macro to format a TWI slave address to write.
 */
#define TWI_SLA_WRITE(SLA) (((SLA) << 1u) | TW_WRITE)

/**
 * @brief Macro to format a TWI slave address to read.
 */
#define TWI_SLA_READ(SLA) (((SLA) << 1u) | TW_READ)

/**
 * @brief Macro to wait until the TWI interrutp flag is set.
 */
#define TWI_WAIT_INTERRUPT_FLAG while (!(TWCR & (1 << TWINT)))

/**
 * @brief ATmega328P 2-wire serial interface registers.
 */
struct twi_memory
{
    /** @brief Bit rate register*/
    uint8_t twbr;
    /** @brief Status register*/
    uint8_t twsr;
    /** @brief Slave address register */
    uint8_t twar;
    /** @brief Data register.*/
    uint8_t twdr;
    /** @brief Control register. */
    uint8_t twcr;
    /** @brief Slave address mask register. */
    uint8_t twamr;
};

/**
 * @brief TWI bit rate prescaler values.
 */
enum twi_bit_rate_prescaler
{
    TWI_PRESCALER_1,
    TWI_PRESCALER_4 = 1 << TWPS0,
    TWI_PRESCALER_16 = 1 << TWPS1,
    TWI_PRESCALER_64 = (1 << TWPS0) | (1 << TWPS1)
};

/**
 * @brief Control register values.
 */
enum twi_control
{
    TWI_SEND_START_CONDITION = (1u << TWINT) | (1u << TWSTA) | (1u << TWEN),
    TWI_SEND_STOP_CONDITION = (1u << TWINT) | (1u << TWSTO) | (1u << TWEN),
    TWI_SET_ENABLED = (1u << TWINT) | (1u << TWEN),
    TWI_OPERATE_AS_SLAVE = (1 << TWEA) | (1 << TWEN)
};

/**
 * @brief Values for the stop parameter in read/write functions. It indicates
 * if a read/write operation is ended with a STOP condition.
 */
enum twi_stop_control
{
    TWI_END_WITHOUT_STOP,
    TWI_END_WITH_STOP
};

/**
 * @brief Transmits a start condition.
 * @return TWI status code.
 */
static inline uint8_t twi_start(void)
{
    TWCR = TWI_SEND_START_CONDITION;
    TWI_WAIT_INTERRUPT_FLAG;
    return TW_STATUS; 
}

/**
 * @brief Transmits a stop condition.
 * @return TWI status code.
 */
static inline uint8_t twi_stop(void)
{
    TWCR = TWI_SEND_STOP_CONDITION;
    TWI_WAIT_INTERRUPT_FLAG;
    return TW_STATUS;
}

/**
 * @brief Transmits one byte.
 * @return TWI status code.
 */
static inline uint8_t twi_transmit(uint8_t data)
{
    TWDR = data;
    TWCR = TWI_SET_ENABLED;
    TWI_WAIT_INTERRUPT_FLAG;
    return TW_STATUS;
}

/**
 * @brief Receives one byte.
 * @return Received byte.
 */
static inline uint8_t twi_receive(void)
{
    TWCR = TWI_SET_ENABLED;
    TWI_WAIT_INTERRUPT_FLAG;
    return TWDR;
}

/**
 * @brief Configures the two wire serial interface.
 * @param bit_rate Target bit rate in Hz. (e.g. 400000)
 */
void twi_configure(uint32_t bit_rate);

/**
 * @brief Writes a sequence of data in master mode.
 * @param sla Slave address.
 * @param src Pointer to data source.
 * @param length Number of bytes to write.
 * @param stop Indicates if a stop condition must be generated after
 * transmitting the last byte.
 * @return Number of successfully written bytes.
 */
uint16_t twi_write(uint8_t sla, uint8_t *src, uint16_t length,
                   enum twi_stop_control stop);

/**
 * @brief Reads a sequence of bytes in master mode.
 * @param sla Slave address.
 * @param dst Pointer to data destination.
 * @param length Number of bytes to read.
 * @param stop Indicates if a stop condition must be generated after receiving
 * the last byte.
 * @return Number of successfully read bytes.
 */
uint16_t twi_read(uint8_t sla, uint8_t *dst, uint16_t length,
                  enum twi_stop_control stop);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !__TWI_H */
