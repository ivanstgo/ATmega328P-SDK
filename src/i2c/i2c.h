/**
 * @file i2c.h
 * @author Iván Santiago
 * @date 07-01-2023 17:55
 * @brief Library to use ATmega328P I2C
*/
#ifndef I2C_H_
#define I2C_H_
#include <avr/io.h>
/**
 * Macro to format I2C slave address to write SLA + W
*/
#define SLA_W(SLA) (SLA) << 1

/**
 * Macro to format I2C slave address to read SLA + R
*/
#define SLA_R(SLA) ((SLA) << 1) | 0x01

/**
 * Inits 2 Wire Serial Interface.
 * TWBR = (F_CPU - 16 * SCLF) / (SCLF * 2 * N)
 */
void i2c_init(void);
/**
 * Sends start condition
 */

static inline void i2c_start(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)))
        ;
}

/**
 * Sends stop condition
 */
static inline void i2c_stop(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

/**
 * Writes a byte using Two Wire Interface
 * @param data the byte to write
 */
static inline void i2c_write(uint8_t data)
{
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)))
        ;
}

/**
 * Write some bytes in the I2C bus
 * @param address adress of the device
 * @param data array cotaining the data
 * @param length number of bytes to write
 * @param stop 0: no stop condition; 1: generate stop condition
*/
void i2c_write_bytes(uint8_t address, uint8_t *data, uint32_t length, uint8_t stop);

/**
 * Reads a byte using Two Wire Interface
 * @return the byte read
 */
unsigned char i2c_read(void);

#endif