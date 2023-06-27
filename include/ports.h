/**
 * @file ports.h
 * @author Iván Santiago
 * @date 06-26-2023 21:39
 * @brief Library to use ATmega328P GPIO
*/
#ifndef _PORTS_H_
#define _PORTS_H_
#include <avr/io.h>
/**
 * Macro to set a pin on port B as output
 * @param PIN the pin to configure in range [0:7]
*/
#define SET_OUTPUT_PORTB(PIN) DDRB |= 1 << (PIN)
/**
 * Macro to set a pin on port C as output
 * @param PIN the pin to configure in range [0:7]
*/
#define SET_OUTPUT_PORTC(PIN) DDRC |= 1 << (PIN)
/**
 * Macro to set a pin on port D as output
 * @param PIN the pin to configure in range [0:7]
*/
#define SET_OUTPUT_PORTD(PIN) DDRD |= 1 << (PIN)
/**
 * Macro to set a pin on port B as input
 * @param PIN the pin to configure in range [0:7]
*/
#define SET_INPUT_PORTB(PIN) DDRB &= ~(1 << (PIN))
/**
 * Macro to set a pin on port C as input
 * @param PIN the pin to configure in range [0:7]
*/
#define SET_INPUT_PORTC(PIN) DDRC &= ~(1 << (PIN))
/**
 * Macro to set a pin on port D as input
 * @param PIN the pin to configure in range [0:7]
*/
#define SET_INPUT_PORTD(PIN) DDRD &= ~(1 << (PIN))
/**
 * Macro to set a pin on port B as input and enable the internal pull-up resistor
 * @param PIN the pin to configure in range [0:7]
*/
#define SET_PULL_UP_PORTB(PIN) DDRB &= ~(1 << (PIN)), PORTB |= 1 << (PIN)
/**
 * Macro to set a pin on port C as input and enable the internal pull-up resistor
 * @param PIN the pin to configure in range [0:7]
*/
#define SET_PULL_UP_PORTC(PIN) DDRC &= ~(1 << (PIN)), PORTC |= 1 << (PIN)
/**
 * Macro to set a pin on port D as input and enable the internal pull-up resistor
 * @param PIN the pin to configure in range [0:7]
*/
#define SET_PULL_UP_PORTD(PIN) DDRD &= ~(1 << (PIN)), PORTD |= 1 << (PIN)
/**
 * Macro to set a pin on port B as tri-state
 * @param PIN the pin to configure in range [0:7]
*/
#define SET_HI_Z_PORTB(PIN) DDRB &= ~(1 << (PIN)), PORTB &= ~(1 << (PIN))
/**
 * Macro to set a pin on port C as tri-state
 * @param PIN the pin to configure in range [0:7]
*/
#define SET_HI_Z_PORTC(PIN) DDRC &= ~(1 << (PIN)), PORTC &= ~(1 << (PIN))
/**
 * Macro to set a pin on port D as tri-state
 * @param PIN the pin to configure in range [0:7]
*/
#define SET_HI_Z_PORTD(PIN) DDRD &= ~(1 << (PIN)), PORTD &= ~(1 << (PIN))
/**
 * Macro to toggle the state of a pin on port B defined as output
 * @param PIN the pin to configure in range [0:7]
 * @note pin must be configured as output
*/
#define TOGGLE_PORTB(PIN) PINB |= 1 << (PIN)
/**
 * Macro to toggle the state of a pin on port C defined as output
 * @param PIN the pin to configure in range [0:7]
 * @note pin must be configured as output
*/
#define TOGGLE_PORTC(PIN) PINC |= 1 << (PIN)
/**
 * Macro to toggle the state of a pin on port D defined as output
 * @param PIN the pin to configure in range [0:7]
 * @note pin must be configured as output
*/
#define TOGGLE_PORTD(PIN) PIND |= 1 << (PIN)
#endif