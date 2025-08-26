/**
 * @file io_pin.c
 * @author Iván Santiago (gh: ivanstgo)
 * @date 25/08/2025 - 19:00
 * @brief ATmega328P I/O ports driver implementation file.
 */

#include <avr/io.h>
#include "drivers/io_pin.h"

/**
 * @brief I/O port registers.
 */
struct io_port
{
    uint8_t PINx;
    uint8_t DDRx;
    uint8_t PORTx;
};

typedef volatile struct io_port * io_port_t;

static io_port_t io_ports[] = {
    [IO_PORTB] = (io_port_t)&PINB, [IO_PORTC] = (io_port_t)&PINC,
    [IO_PORTD] = (io_port_t)&PIND
};

void io_pin_configure(struct pin_config config)
{
    uint8_t port = config.pin >> PORT_OFFSET;
    uint8_t pin = (config.pin >> PIN_OFFSET) & 0b111;
    if (config.dir == OUTPUT)
    {
        io_ports[port]->DDRx |= 1u << pin;
        if (config.value == HIGH)
        {
            io_ports[port]->PORTx |= 1u << pin;
        }
        else
        {
            io_ports[port]->PORTx &= ~(1u << pin);
        }
    }
    else
    {
        io_ports[port]->DDRx &= ~(1u << pin);
        if (config.pull_up == PULL_UP_ENABLED)
        {
            io_ports[port]->PORTx |= 1u << pin;
        }
        else
        {
            io_ports[port]->PORTx &= ~(1u << pin);
        }
    }
}

uint8_t io_pin_read(enum io_pin pin)
{
    uint8_t port = pin >> PORT_OFFSET;
    uint8_t p = (pin >> PIN_OFFSET) & 0b111;
    uint8_t value = io_ports[port]->PINx; 
    return (value >> p) & 0x01;
}

void io_pin_write(enum io_pin pin, enum io_value value)
{
    uint8_t port = pin >> PORT_OFFSET;
    uint8_t p = (pin >> PIN_OFFSET) & 0b111;
    if (value == HIGH)
    {
        io_ports[port]->PORTx |= 1u << p;
    }
    else
    {
        io_ports[port]->PORTx &= ~(1u << p);
    }
}

void io_pin_toggle(enum io_pin pin)
{
    uint8_t port = pin >> PORT_OFFSET;
    uint8_t p = (pin >> PIN_OFFSET) & 0b111;
    // Writing a logic one to PINxn toggles the value of PORTxn
    io_ports[port]->PINx |= 1 << p;
}
