#include "io_pin.h"
#include <avr/io.h>

static volatile uint8_t *ports_ddrx[] = {[IO_PORTB] = &DDRB, [IO_PORTC] = &DDRC, [IO_PORTD] = &DDRD};
static volatile uint8_t *ports_pinx[] = {[IO_PORTB] = &PINB, [IO_PORTC] = &PINC, [IO_PORTD] = &PIND};
static volatile uint8_t *ports_portx[] = {[IO_PORTB] = &PORTB, [IO_PORTC] = &PORTC, [IO_PORTD] = &PORTD};

void io_pin_configure(struct pin_config config)
{
    uint8_t port = config.pin >> PORT_OFFSET;
    uint8_t pin = (config.pin >> PIN_OFFSET) & 0b111;
    if (config.dir == OUTPUT)
    {
        *(ports_ddrx[port]) |= 1u << pin;
        if (config.value == HIGH)
        {
            *(ports_portx[port]) |= (1u << pin);
        }
        else
        {
            *(ports_portx[port]) &= ~(1u << pin);
        }
    }
    else
    {
        *(ports_ddrx[port]) &= ~(1u << pin);
        if (config.pull_up == PULL_UP_ENABLED)
        {
            *(ports_portx[port]) |= (1u << pin);
        }
        else
        {
            *(ports_portx[port]) &= ~(1u << pin);
        }
    }
}

uint8_t io_pin_read(enum io_pin pin)
{
    uint8_t port = pin >> PORT_OFFSET;
    uint8_t p = (pin >> PIN_OFFSET) & 0b111;
    uint8_t value = *(ports_pinx[port]);
    return (value >> p) & 0x01;
}

void io_pin_write(enum io_pin pin, enum io_value value)
{
    uint8_t port = pin >> PORT_OFFSET;
    uint8_t p = (pin >> PIN_OFFSET) & 0b111;
    if (value == HIGH)
    {
        *(ports_portx[port]) |= (1u << p);
    }
    else
    {
        *(ports_portx[port]) &= ~(1u << p);
    }
}

void io_pin_toggle(enum io_pin pin)
{
    uint8_t port = pin >> PORT_OFFSET;
    uint8_t p = (pin >> PIN_OFFSET) & 0b111;
    // Writing a logic one to PINxn toggles the value of PORTxn
    *(ports_pinx[port]) |= (1 << p);   
}