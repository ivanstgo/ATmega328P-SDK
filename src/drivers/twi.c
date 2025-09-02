/**
 * @file twi.c
 * @author Iván Santiago (https://github.com/ivanstgo)
 * @date 25/08/2025 - 23:19
 * @brief ATmega328P 2-wire serial interface driver.
 */

#include "drivers/twi.h"

#ifndef F_CPU
#define F_CPU 16000000ul
#warning "Using F_CPU=16000000ul for bit rate calculation as it has not been defined."
#endif /* !F_CPU */

#define TWI_PRESCALER 1.0f

void twi_configure(uint32_t bit_rate)
{
    TWSR = TWI_PRESCALER_VALUE_1;
    float br = (((float)F_CPU / (float)bit_rate) - 16.0f) /
               (2.0f * TWI_PRESCALER);
    TWBR = (uint8_t)br;
    TWCR = 0;
}

uint16_t twi_write(uint8_t sla, uint8_t *src, uint16_t length)
{
    twi_start();
    twi_transmit(TWI_SLA_WRITE(sla));
    if (TW_STATUS != TW_MT_SLA_ACK)
    {
        return 0;
    }
    uint16_t i = 0;
    while (i < length)
    {
        twi_transmit(src[i]);
        if (TW_STATUS != TW_MT_DATA_ACK)
        {
            break;
        }
        i++;
    }
    twi_stop();
    return i;
}

uint16_t twi_read(uint8_t sla, uint8_t *dst, uint16_t length)
{
    twi_start();
    twi_transmit(TWI_SLA_READ(sla));
    if (TW_STATUS != TW_MR_SLA_ACK)
    {
        return 0;
    }
    uint16_t i = 0;
    while (i < length)
    {
        dst[i] = twi_receive();
        if (TW_STATUS != TW_MR_DATA_ACK)
        {
            break;
        }
        i++;
    }
    twi_stop();
    return i;
}
