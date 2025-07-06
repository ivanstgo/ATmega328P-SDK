/**
 * @file io.h
 * @author Iván Santiago (gh:ivanstgo)
 * @date 29/06/2025 - 17:07
 * @brief AVR IO ports driver
*/
#ifndef IO_PIN_H_
#define IO_PIN_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>

enum port
{
    IO_PORTB,
    IO_PORTC,
    IO_PORTD
};

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

enum io_dir
{
    INPUT,
    OUTPUT
};

enum io_value
{
    LOW,
    HIGH
};

enum io_pullup
{
    PULL_UP_ENABLED,
    PULL_UP_DISABLED
};

#define PORT_OFFSET 6
#define PIN_OFFSET 3

/**
 * @brief This enum encodes each I/O pin function as follows: port[7:6]pin[5-3]func[2:0]
 */
enum io_pin
{
    // Port B
    PIN_ICP1 = (IO_PORTB << PORT_OFFSET) | (IO_PIN0 << PIN_OFFSET), /** Timer/Counter 1 input capture input */
    PIN_CLKO, /** divided system clock output */
    PIN_PCINT0, /** pin change interrupt 0 */
    PIN_B0, /** GPIO Port B pin 0 */
    PIN_OC1A = (IO_PORTB << PORT_OFFSET) | (IO_PIN1 << PIN_OFFSET), /** Timer/Counter 1 output compare match A output */
    PIN_PCINT1, /** pin change interrupt 1 */
    PIN_B1, /** GPIO Port B pin 1 */
    PIN_SS = (IO_PORTB << PORT_OFFSET) | (IO_PIN2 << PIN_OFFSET), /** SPI bus master slave select */
    PIN_OC1B, /** Timer/Counter 1 output compare match B output */
    PIN_PCINT2, /** pin change interrupt 2 */
    PIN_B2, /** GPIO Port B pin 2 */
    PIN_MOSI = (IO_PORTB << PORT_OFFSET) | (IO_PIN3 << PIN_OFFSET), /** SPI bus master output/slave input */
    PIN_OC2A, /** Timer/Counter 2 output compare match A output */
    PIN_PCINT3, /** pin change interrupt 3 */
    PIN_B3, /** GPIO Port B pin 3 */
    PIN_MISO = (IO_PORTB << PORT_OFFSET) | (IO_PIN4 << PIN_OFFSET), /** SPI bus master input/slave output */
    PIN_PCINT4, /** pin change interrupt 4 */
    PIN_B4, /** GPIO Port B pin 4 */
    PIN_SCK = (IO_PORTB << PORT_OFFSET) | (IO_PIN5 << PIN_OFFSET), /** SPI bus master clock input */
    PIN_PCINT5, /** pin change interrupt 5 */
    PIN_B5, /** GPIO Port B pin 5 */
    PIN_XTAL1 = (IO_PORTB << PORT_OFFSET) | (IO_PIN6 << PIN_OFFSET), /** Chip clock oscillator pin 1 or external clock input */
    PIN_TOSC1, /** timer oscillator pin 1 */
    PIN_PCINT6, /** pin change interrupt 6 */
    PIN_B6, /** GPIO Port B pin 6 */
    PIN_XTAL2 = (IO_PORTB << PORT_OFFSET) | (IO_PIN7 << PIN_OFFSET), /** Chip clock oscillator pin 2 */
    PIN_TOSC2, /** timer oscillator pin 2 */
    PIN_PCINT7, /** pin change interrupt 7 */
    PIN_B7, /** GPIO Port B pin 7 */
    // Port C
    PIN_ADC0 = (IO_PORTC << PORT_OFFSET) | (IO_PIN0 << PIN_OFFSET), /** ADC input channel 0 */
    PIN_PCINT8, /** pin change interrupt 8 */
    PIN_C0, /** GPIO Port C pin 0 */
    PIN_ADC1 = (IO_PORTC << PORT_OFFSET) | (IO_PIN1 << PIN_OFFSET), /** ADC input channel 1 */
    PIN_PCINT9, /** pin change interrupt 9 */
    PIN_C1, /** GPIO Port C pin 1 */
    PIN_ADC2 = (IO_PORTC << PORT_OFFSET) | (IO_PIN2 << PIN_OFFSET), /** ADC input channel 2 */
    PIN_PCINT10, /** pin change interrupt 10 */
    PIN_C2, /** GPIO Port C pin 2 */
    PIN_ADC3 = (IO_PORTC << PORT_OFFSET) | (IO_PIN3 << PIN_OFFSET), /** ADC input channel 3 */
    PIN_PCINT11, /** pin change interrupt 11 */
    PIN_C3, /** GPIO Port C pin 3 */
    PIN_ADC4 = (IO_PORTC << PORT_OFFSET) | (IO_PIN4 << PIN_OFFSET), /** ADC input channel 4 */
    PIN_SDA, /** 2-wire serial bus data input/output line */
    PIN_PCINT12, /** pin change interrupt 12 */
    PIN_C4, /** GPIO Port C pin 4 */
    PIN_ADC5 = (IO_PORTC << PORT_OFFSET) | (IO_PIN5 << PIN_OFFSET), /** ADC input channel 4 */
    PIN_SCL, /** 2-wire serial bus clock line */
    PIN_PCINT13, /** pin change interrupt 13 */
    PIN_C5, /** GPIO Port C pin 5 */
    PIN_RESET = (IO_PORTC << PORT_OFFSET) | (IO_PIN6 << PIN_OFFSET), /** reset pin */
    PIN_PCINT14, /** pin change interrupt 14 */
    PIN_C6, /** GPIO Port C pin 6 */
    // Port D
    PIN_RXD = (IO_PORTD << PORT_OFFSET) | (IO_PIN0 << PIN_OFFSET), /** USART input pin */
    PIN_PCINT16, /** pin change interrupt 16 */
    PIN_D0, /** GPIO Port D pin 0 */
    PIN_TXD = (IO_PORTD << PORT_OFFSET) | (IO_PIN1 << PIN_OFFSET), /** USART output pin */
    PIN_PCINT17, /** pin change interrupt 17 */
    PIN_D1, /** GPIO Port D pin 1 */
    PIN_INT0 = (IO_PORTD << PORT_OFFSET) | (IO_PIN2 << PIN_OFFSET), /** external interrupt 0 input */
    PIN_PCINT18, /** pin change interrupt 18 */
    PIN_D2, /** GPIO Port D pin 2 */
    PIN_INT1 = (IO_PORTD << PORT_OFFSET) | (IO_PIN3 << PIN_OFFSET), /** external interrupt 1 input */
    PIN_OC2B, /** Timer/Counter 2 output compare match B output */
    PIN_PCINT19, /** pin change interrupt 19 */
    PIN_D3, /** GPIO Port D pin 3 */
    PIN_XCK = (IO_PORTD << PORT_OFFSET) | (IO_PIN4 << PIN_OFFSET), /** USART external clock input/output */
    PIN_T0, /** Timer/Counter 0 external counter input */
    PIN_PCINT20, /** pin change interrupt 20 */
    PIN_D4, /** GPIO Port D pin 4 */
    PIN_T1 = (IO_PORTD << PORT_OFFSET) | (IO_PIN5 << PIN_OFFSET),  /** Timer/Counter 1 external counter input */
    PIN_OC0B, /** Timer/Counter 0 output compare match B output */
    PIN_PCINT21, /** pin change interrupt 21 */
    PIN_D5, /** GPIO Port D pin 5 */
    PIN_AIN0 = (IO_PORTD << PORT_OFFSET) | (IO_PIN6 << PIN_OFFSET), /** analog comparator positive input */
    PIN_OC0A, /** Timer/Counter 0 output compare match A output */
    PIN_PCINT22, /** pin change interrupt 22 */
    PIN_D6, /** GPIO Port D pin 6 */
    PIN_AIN1 = (IO_PORTD << PORT_OFFSET) | (IO_PIN7 << PIN_OFFSET), /** analog comparator negative input */
    PIN_PCINT23, /** pin change interrupt 23 */
    PIN_D7, /** GPIO Port D pin 7 */
};

struct pin_config
{
    enum io_pin pin;
    enum io_dir dir;
    enum io_pullup pull_up;
    enum io_value value;
};

/**
 * @brief Configures a pin using a pin_config struct
 * @param config pin configuration
 */
void io_pin_configure(struct pin_config config);

/**
 * @brief Reads the logic level on a pin
 * @param pin pin
 * @return pin logic level
 */
uint8_t io_pin_read(enum io_pin pin);

/**
 * @brief Writes a logic level on a pin
 * @param pin pin
 * @param value new pin value
 */
void io_pin_write(enum io_pin pin, enum io_value value);

/**
 * @brief Toggles the value of a pin
 * @param pin pin
 */
void io_pin_toggle(enum io_pin pin);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IO_PIN_H_ */
