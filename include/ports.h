/**
 * @file ports.h
 * @brief Library to use the ATmega328P GPIO
 * @author Iván Santiago
 * @date 2023-08-12 21:54
 */
#ifndef PORTS_H_
#define PORTS_H_
#include <avr/io.h>
#include <avr/interrupt.h>

typedef enum pin_number
{
    PIN_0,
    PIN_1,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6,
    PIN_7
} PinNumber;

typedef enum direction
{
    INPUT,
    OUTPUT,
    INPUT_PULL_UP,
    HI_Z,
} Direction;

typedef enum arduino_pin
{
    D0,
    D1,
    D2,
    D3,
    D4,
    D5,
    D6,
    D7,
    D8,
    D9,
    D10,
    D11,
    D12,
    D13,
    D14,
    D15,
    D16,
    D17,
    D18,
    D19
} ArduinoPin;

typedef enum sense_control
{
    LOW_LEVEL,
    ANY_LOGICAL_CHANGE,
    FALLING_EDGE,
    RISING_EDGE
} SenseControl;

/**
 * Set the direction of a pin from the port B
 * @param pin number of pin
 * @param dir pin direction INPUT, OUTPUT, INPUT_PULL_UP, HI_Z
 */
static inline void portB_set_dir(PinNumber pin, Direction dir)
{
    switch (dir)
    {
    case INPUT:
        DDRB &= ~(1 << pin);
        break;
    case OUTPUT:
        DDRB |= 1 << pin;
        break;
    case INPUT_PULL_UP:
        DDRB &= ~(1 << pin);
        PORTB |= 1 << pin;
        break;
    default:
        DDRB &= ~(1 << pin);
        PORTB &= ~(1 << pin);
        break;
    }
}

/**
 * Set the direction of a pin from the port C
 * @param pin number of pin
 * @param dir pin direction INPUT, OUTPUT, HI_Z
 */
static inline void portC_set_dir(PinNumber pin, Direction dir)
{
    switch (dir)
    {
    case INPUT:
        DDRC &= ~(1 << pin);
        break;
    case OUTPUT:
        DDRC |= 1 << pin;
        break;
    case INPUT_PULL_UP:
        DDRC &= ~(1 << pin);
        PORTC |= 1 << pin;
        break;
    default:
        DDRC &= ~(1 << pin);
        PORTC &= ~(1 << pin);
        break;
    }
}

/**
 * Set the direction of a pin from the port D
 * @param pin number of pin
 * @param dir pin direction INPUT, OUTPUT, HI_Z
 */
static inline void portD_set_dir(PinNumber pin, Direction dir)
{
    switch (dir)
    {
    case INPUT:
        DDRD &= ~(1 << pin);
        break;
    case OUTPUT:
        DDRD |= 1 << pin;
        break;
    case INPUT_PULL_UP:
        DDRD &= ~(1 << pin);
        PORTD |= 1 << pin;
        break;
    default:
        DDRD &= ~(1 << pin);
        PORTD &= ~(1 << pin);
        break;
    }
}

/**
 * Clears the PUD bit from the MCUCR register
 */
static inline void enable_pull_up(void)
{
    MCUCR &= ~(1 << PUD);
}

/**
 * Sets the PUD bit from the MCUCR register
 */
static inline void disable_pull_up(void)
{
    MCUCR |= 1 << PUD;
}

/**
 * Sets the direction of Arduino UNO board pin
 * @param arduino_pin pin from Arduino UNO board
 * @param dir pin direction INPUT, OUTPUT, HI_Z
 */
void arduino_pin_set_dir(ArduinoPin arduino_pin, Direction dir);

/**
 * Put a logic value in a pin from the port B
 * @param pin pin number
 * @param value 0 logic or 1 logic
*/
static inline void portB_write(PinNumber pin, unsigned char value)
{
    if (value)
        PORTB |= 1 << pin;
    else
        PORTB &= ~(1 << pin);
}

/**
 * Put a logic value in a pin from the port C
 * @param pin pin number
 * @param value 0 logic or 1 logic
*/
static inline void portC_write(PinNumber pin, unsigned char value)
{
    if (value)
        PORTC |= 1 << pin;
    else
        PORTC &= ~(1 << pin);
}

/**
 * Put a logic value in a pin from the port D
 * @param pin pin number
 * @param value 0 logic or 1 logic
*/
static inline void portD_write(PinNumber pin, unsigned char value)
{
    if (value)
        PORTD |= 1 << pin;
    else
        PORTD &= ~(1 << pin);
}

/**
 * Read the value of a pin from the port B
 * @param pin pin to read
*/
static inline unsigned char portB_read(PinNumber pin)
{
    asm volatile("nop");
    return PINB & (1 << pin);
}

/**
 * Read the value of a pin from the port C
 * @param pin pin to read
*/
static inline unsigned char portC_read(PinNumber pin)
{
    asm volatile("nop");
    return PINC & (1 << pin);
}

/**
 * Read the value of a pin from the port D
 * @param pin pin to read
*/
static inline unsigned char portD_read(PinNumber pin)
{
    asm volatile("nop");
    return PIND & (1 << pin);
}

/**
 * Toggles the out of a pin form the port B
 * @param pin pin number
*/
static inline void portB_toggle(PinNumber pin)
{
    PINB |= 1 << pin;
}

/**
 * Toggles the out of a pin form the port C
 * @param pin pin number
*/
static inline void portC_toggle(PinNumber pin)
{
    PINC |= 1 << pin;
}

/**
 * Toggles the out of a pin form the port D
 * @param pin pin number
*/
static inline void portD_toggle(PinNumber pin)
{
    PIND |= 1 << pin;
}

/**
 * Enables the external interrup 0
 * @param trigger event that triggers the interrupt
 * @note The interrupt service routine must be defined:
 * #include <avr/interrupt.h>
 * ISR(INT0_vect) {..}
*/
static inline void external_interrup0_enable(SenseControl trigger)
{
    EICRA |= trigger;
    EIMSK |= 0x01;
    sei();
}

/**
 * Enables the external interrup 1
 * @param trigger event that triggers the interrupt
 * @note The interrupt service routine must be defined:
 * #include <avr/interrupt.h>
 * ISR(INT1_vect) {..}
*/
static inline void external_interrup1_enable(SenseControl trigger)
{
    EICRA |= trigger << 2;
    EIMSK |= 0x02;
    sei();
}

/**
 * Writes a value to an Arduino UNO board pin
 * @param arduino_pin pin to write
 * @param value 0 or 1
*/
void arduino_pin_write(ArduinoPin arduino_pin, unsigned char value);

/**
 * Toggles the value of an Arduino UNO board pin
 * @param arduino_pin UNO board pin (0 to 19)
*/
void arduino_pin_toggle(ArduinoPin arduino_pin);

/**
 * Reads the value of an Arduino UNO board pin
 * @param arduino_pin UNO board pin (0 to 19)
*/
unsigned char arduino_pin_read(ArduinoPin arduino_pin);

#endif