/**
 * @file io_pin.h
 * @author Iván Santiago (gh: ivanstgo)
 * @date 25/08/2025 - 17:00
 * @brief ATmega328P I/O ports driver.
*/

#ifndef __IO_PIN_H
#define __IO_PIN_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>

/**
 * @brief This enumeration lists the ATmega328P I/O ports.
 */
enum port
{
    IO_PORTB,
    IO_PORTC,
    IO_PORTD
};

/**
 * @brief This enumeration lists the ATmega328P I/O pins of each port.
 */
enum pin_num
{
    IO_PIN0,
    IO_PIN1,
    IO_PIN2,
    IO_PIN3,
    IO_PIN4,
    IO_PIN5,
    IO_PIN6,
    IO_PIN7
};

/**
 * @brief I/O pin possible directions.
 */
enum io_dir
{
    INPUT,
    OUTPUT
};

/**
 * @brief I/O pin possible logic values.
 */
enum io_value
{
    LOW,
    HIGH
};

/**
 * @brief I/O pin built-in pull-up resistor status.
 */
enum io_pullup
{
    PULL_UP_ENABLED,
    PULL_UP_DISABLED
};

#define PORT_OFFSET 6
#define PIN_OFFSET 3

/**
 * @brief This enum encodes each I/O pin function as follows:
 * port[7:6]pin[5-3]func[2:0]
 */
enum io_pin
{
    /** @brief Timer/Counter 1 input capture input */
    PIN_ICP1 = (IO_PORTB << PORT_OFFSET) | (IO_PIN0 << PIN_OFFSET),
    /** @brief divided system clock output */
    PIN_CLKO,
    /** @brief pin change interrupt 0 */
    PIN_PCINT0,
    /** @brief GPIO Port B pin 0 */
    PIN_B0,
    /** @brief Timer/Counter 1 output compare match A output */
    PIN_OC1A = (IO_PORTB << PORT_OFFSET) | (IO_PIN1 << PIN_OFFSET),
    /** @brief pin change interrupt 1 */
    PIN_PCINT1,
    /** @brief GPIO Port B pin 1 */
    PIN_B1,
    /** @brief SPI bus master slave select */
    PIN_SS = (IO_PORTB << PORT_OFFSET) | (IO_PIN2 << PIN_OFFSET),
    /** @brief Timer/Counter 1 output compare match B output */
    PIN_OC1B,
    /** @brief pin change interrupt 2 */
    PIN_PCINT2,
    /** @brief GPIO Port B pin 2 */
    PIN_B2,
    /** @brief SPI bus master output/slave input */
    PIN_MOSI = (IO_PORTB << PORT_OFFSET) | (IO_PIN3 << PIN_OFFSET),
    /** @brief Timer/Counter 2 output compare match A output */
    PIN_OC2A,
    /** @brief pin change interrupt 3 */
    PIN_PCINT3,
    /** @brief GPIO Port B pin 3 */
    PIN_B3,
    /** @brief SPI bus master input/slave output */
    PIN_MISO = (IO_PORTB << PORT_OFFSET) | (IO_PIN4 << PIN_OFFSET),
    /** @brief pin change interrupt 4 */
    PIN_PCINT4,
    /** @brief GPIO Port B pin 4 */
    PIN_B4,
    /** @brief SPI bus master clock input */
    PIN_SCK = (IO_PORTB << PORT_OFFSET) | (IO_PIN5 << PIN_OFFSET),
    /** @brief pin change interrupt 5 */
    PIN_PCINT5,
    /** @brief GPIO Port B pin 5 */
    PIN_B5,
    /** @brief Chip clock oscillator pin 1 or external clock input */
    PIN_XTAL1 = (IO_PORTB << PORT_OFFSET) | (IO_PIN6 << PIN_OFFSET),
    /** @brief timer oscillator pin 1 */
    PIN_TOSC1,
    /** @brief pin change interrupt 6 */
    PIN_PCINT6,
    /** @brief GPIO Port B pin 6 */
    PIN_B6,
    /** @brief Chip clock oscillator pin 2 */
    PIN_XTAL2 = (IO_PORTB << PORT_OFFSET) | (IO_PIN7 << PIN_OFFSET),
    /** @brief timer oscillator pin 2 */
    PIN_TOSC2,
    /** @brief pin change interrupt 7 */
    PIN_PCINT7,
    /** @brief GPIO Port B pin 7 */
    PIN_B7,
    /** @brief ADC input channel 0 */
    PIN_ADC0 = (IO_PORTC << PORT_OFFSET) | (IO_PIN0 << PIN_OFFSET),
    /** @brief pin change interrupt 8 */
    PIN_PCINT8,
    /** @brief GPIO Port C pin 0 */
    PIN_C0,
    /** @brief ADC input channel 1 */
    PIN_ADC1 = (IO_PORTC << PORT_OFFSET) | (IO_PIN1 << PIN_OFFSET),
    /** @brief pin change interrupt 9 */
    PIN_PCINT9,
    /** @brief GPIO Port C pin 1 */
    PIN_C1,
    /** @brief ADC input channel 2 */
    PIN_ADC2 = (IO_PORTC << PORT_OFFSET) | (IO_PIN2 << PIN_OFFSET),
    /** @brief pin change interrupt 10 */
    PIN_PCINT10,
    /** @brief GPIO Port C pin 2 */
    PIN_C2,
    /** @brief ADC input channel 3 */
    PIN_ADC3 = (IO_PORTC << PORT_OFFSET) | (IO_PIN3 << PIN_OFFSET),
    /** @brief pin change interrupt 11 */
    PIN_PCINT11,
    /** @brief GPIO Port C pin 3 */
    PIN_C3,
    /** @brief ADC input channel 4 */
    PIN_ADC4 = (IO_PORTC << PORT_OFFSET) | (IO_PIN4 << PIN_OFFSET),
    /** @brief 2-wire serial bus data input/output line */
    PIN_SDA,
    /** @brief pin change interrupt 12 */
    PIN_PCINT12,
    /** @brief GPIO Port C pin 4 */
    PIN_C4,
    /** @brief ADC input channel 4 */
    PIN_ADC5 = (IO_PORTC << PORT_OFFSET) | (IO_PIN5 << PIN_OFFSET),
    /** @brief 2-wire serial bus clock line */
    PIN_SCL,
    /** @brief pin change interrupt 13 */
    PIN_PCINT13,
    /** @brief GPIO Port C pin 5 */
    PIN_C5,
    /** @brief reset pin */
    PIN_RESET = (IO_PORTC << PORT_OFFSET) | (IO_PIN6 << PIN_OFFSET),
    /** @brief pin change interrupt 14 */
    PIN_PCINT14,
    /** @brief GPIO Port C pin 6 */
    PIN_C6,
    /** @brief USART input pin */
    PIN_RXD = (IO_PORTD << PORT_OFFSET) | (IO_PIN0 << PIN_OFFSET),
    /** @brief pin change interrupt 16 */
    PIN_PCINT16,
    /** @brief GPIO Port D pin 0 */
    PIN_D0,
    /** @brief USART output pin */
    PIN_TXD = (IO_PORTD << PORT_OFFSET) | (IO_PIN1 << PIN_OFFSET),
    /** @brief pin change interrupt 17 */
    PIN_PCINT17,
    /** @brief GPIO Port D pin 1 */
    PIN_D1,
    /** @brief external interrupt 0 input */
    PIN_INT0 = (IO_PORTD << PORT_OFFSET) | (IO_PIN2 << PIN_OFFSET),
    /** @brief pin change interrupt 18 */
    PIN_PCINT18,
    /** @brief GPIO Port D pin 2 */
    PIN_D2,
    /** @brief external interrupt 1 input */
    PIN_INT1 = (IO_PORTD << PORT_OFFSET) | (IO_PIN3 << PIN_OFFSET),
    /** @brief Timer/Counter 2 output compare match B output */
    PIN_OC2B,
    /** @brief pin change interrupt 19 */
    PIN_PCINT19,
    /** @brief GPIO Port D pin 3 */
    PIN_D3,
    /** @brief USART external clock input/output */
    PIN_XCK = (IO_PORTD << PORT_OFFSET) | (IO_PIN4 << PIN_OFFSET),
    /** @brief Timer/Counter 0 external counter input */
    PIN_T0,
    /** @brief pin change interrupt 20 */
    PIN_PCINT20,
    /** @brief GPIO Port D pin 4 */
    PIN_D4,
    /** @brief Timer/Counter 1 external counter input */
    PIN_T1 = (IO_PORTD << PORT_OFFSET) | (IO_PIN5 << PIN_OFFSET), 
    /** @brief Timer/Counter 0 output compare match B output */
    PIN_OC0B,
    /** @brief pin change interrupt 21 */
    PIN_PCINT21,
    /** @brief GPIO Port D pin 5 */
    PIN_D5,
    /** @brief analog comparator positive input */
    PIN_AIN0 = (IO_PORTD << PORT_OFFSET) | (IO_PIN6 << PIN_OFFSET),
    /** @brief Timer/Counter 0 output compare match A output */
    PIN_OC0A,
    /** @brief pin change interrupt 22 */
    PIN_PCINT22,
    /** @brief GPIO Port D pin 6 */
    PIN_D6,
    /** @brief analog comparator negative input */
    PIN_AIN1 = (IO_PORTD << PORT_OFFSET) | (IO_PIN7 << PIN_OFFSET),
    /** @brief pin change interrupt 23 */
    PIN_PCINT23,
    /** @brief GPIO Port D pin 7 */
    PIN_D7,
};

/**
 * @brief IO pin configuration struct.
 */
struct pin_config
{
    enum io_pin pin;
    enum io_dir dir;
    enum io_pullup pull_up;
    enum io_value value;
};

/**
 * @brief Configures a pin using a pin_config struct.
 * @param config Pin configuration.
 */
void io_pin_configure(struct pin_config config);

/**
 * @brief Reads the logic level on a pin.
 * @param pin Input pin.
 * @return Pin logic level.
 */
uint8_t io_pin_read(enum io_pin pin);

/**
 * @brief Writes a logic level on a pin.
 * @param pin Output pin.
 * @param value New pin logic value.
 */
void io_pin_write(enum io_pin pin, enum io_value value);

/**
 * @brief Toggles the value of a pin.
 * @param pin Output pin.
 */
void io_pin_toggle(enum io_pin pin);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IO_PIN_H_ */
