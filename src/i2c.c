#include "i2c.h"
#include <avr/io.h>
/**
 * Inits 2 Wire Serial Interface.
 * TWBR = (F_CPU - 16 * SCLF) / (SCLF * 2 * N)
 */
void i2c_init(void)
{
    // TWSR = 1 << TWPS0;
    TWSR = 0;
    TWBR = 12;
    TWCR = 1 << TWEN;
}

/**
 * Sends start condition
 */
void i2c_start(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)))
        ;
}

/**
 * Sends stop condition
 */
void i2c_stop(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

/**
 * Writes a byte using Two Wire Interface
 * @param data the byte to write
 */
void i2c_write(unsigned char data)
{
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)))
        ;
}

/**
 * Reads a byte using Two Wire Interface
 * @return the byte read
 */
unsigned char i2c_read(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)))
        ;
    return TWDR;
}