/**
 * @file twi.h
 * @author Iván Santiago (https://github.com/ivanstgo)
 * @date 25/08/2025 - 20:04
 * @brief ATmega328P 2-wire serial interface driver.
 */

#ifndef __TWI_H
#define __TWI_H

#include <stdint.h>
#include <avr/io.h>
#include <util/twi.h>

/**
 * @brief Macro to format a slave address for reading.
 */
#define TWI_SLA_WRITE(SLA) (((SLA) << 1u) | TW_WRITE)

/**
 * @brief Macro to format a slave address for writing.
 */
#define TWI_SLA_READ(SLA) (((SLA) << 1u) | TW_READ)

/**
 * @brief Prescaler value.
 */
enum twi_prescaler
{
    TWI_PRESCALER_VALUE_1,
    TWI_PRESCALER_VALUE_4 = _BV(TWPS0),
    TWI_PRESCALER_VALUE_16 = _BV(TWPS1),
    TWI_PRESCALER_VALUE_64 = _BV(TWPS0) | _BV(TWPS1)
};

/**
 * @brief This enumeration lists values to write into the TWI control register.
 */
enum twi_control_byte
{
    TWI_SEND_START_CONDITION = _BV(TWEN) | _BV(TWSTA) | _BV(TWINT),
    TWI_SEND_STOP_CONDITION = _BV(TWEN) | _BV(TWSTO) | _BV(TWINT),
    TWI_TRANSMIT_BYTE = _BV(TWEN) | _BV(TWEA) | _BV(TWINT),
    TWI_RECEIVE_BYTE = TWI_TRANSMIT_BYTE,
};

/**
 * @brief Generates a start condition.
 */
static inline void twi_start(void)
{
    TWCR = TWI_SEND_START_CONDITION;
    loop_until_bit_is_set(TWCR, TWINT);
}

/**
 * @brief Generates a stop condition.
 */
static inline void twi_stop(void)
{
    TWCR = TWI_SEND_STOP_CONDITION;
}

/**
 * @brief Transmits a byte.
 * @param data Byte to bre transmitted.
 */
static inline void twi_transmit(uint8_t data)
{
    TWDR = data;
    TWCR = TWI_TRANSMIT_BYTE;
    loop_until_bit_is_set(TWCR, TWINT);
}

/**
 * @brief Receives a byte.
 * @return Received byte.
 */
static inline uint8_t twi_receive(void)
{
    TWCR = TWI_RECEIVE_BYTE;
    loop_until_bit_is_set(TWCR, TWINT);
    return TWDR;
}

/**
 * @brief Configures the 2-wire serial interface.
 * @param bit_rate Bit rate in Hz e.g. 100000.
 */
void twi_configure(uint32_t bit_rate);

/**
 * @brief Writes data to a slave.
 * @param sla Slave address.
 * @param src Data source.
 * @param length Number of bytes to transmit.
 */
uint16_t twi_write(uint8_t sla, uint8_t *src, uint16_t length);

/**
 * @brief Reads data from a slave.
 * @param sla Slave address.
 * @param dst Data destination.
 * @param length Number of bytes to receive.
 */
uint16_t twi_read(uint8_t sla, uint8_t *dst, uint16_t length);

#endif /* !__TWI_H */
