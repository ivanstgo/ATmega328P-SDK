#include "i2c.h"
#include <avr/io.h>

void i2c_init(void)
{
    // TWSR = 1 << TWPS0;
    TWSR = 0;
    TWBR = 12;
    TWCR = 1 << TWEN;
}

unsigned char i2c_read(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)))
        ;
    return TWDR;
}

void i2c_write_bytes(uint8_t address, uint8_t *data, uint32_t length, uint8_t stop)
{
    i2c_start();
    i2c_write(SLA_W(address));
    for (uint32_t i = 0; i < length; i++)
        i2c_write(*(data + i));
    if (stop)
        i2c_stop();
}