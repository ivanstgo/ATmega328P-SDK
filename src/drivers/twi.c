/**
 * @file twi.c
 * @author Iván Santiago (gh: ivanstgo)
 * @date 25/08/2025 - 23:19
 * @brief ATmega328P 2-wire serial interface driver implementation file.
 */

#include "drivers/twi.h"

#ifndef F_CPU
#define F_CPU 16000000ul
#warning Using F_CPU=16000000ul as it has not been defined.
#endif /* !F_CPU */

#define TWI_PRESCALER 1.0f

void twi_configure(uint32_t bit_rate)
{
    float twbr = (((float)F_CPU / (float)bit_rate) - 16.0f) / (2.0f * TWI_PRESCALER);
    TWBR = (uint8_t) twbr;
}

uint16_t twi_write(uint8_t sla, uint8_t *src, uint16_t length)
{
    uint16_t i = 0;
    twi_start();
    if (twi_transmit(TWI_SLA_WRITE(sla)) != TW_MT_SLA_ACK)
    {
        twi_stop();
        return i;
    };
    for (i = 0; i < length; i++)
    {
        if (twi_transmit(src[i]) != TW_MR_DATA_ACK) break;
    }
    twi_stop();
    return i;
}

uint16_t twi_read(uint8_t sla, uint8_t *dst, uint16_t length)
{
    // TODO: Implement master read function.
}
