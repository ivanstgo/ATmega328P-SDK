/**
 * @file led_blink.c
 * @author Iván Santiago (https://github.com/ivanstgo)
 * @date 25/08/2025 - 18:44
 * @brief This example program blinks an LED conected to the PB5 I/O pin.
 */
#include <util/delay.h>
#include "drivers/io_pin.h"

int main(void)
{
    struct pin_config led_pin = {
        .pin = PIN_B5,
        .dir = OUTPUT,
        .pull_up = PULL_UP_DISABLED,
        .value = LOW
    };
    pin_configure(led_pin);

    while(1)
    {
        pin_toggle(led_pin.pin);
        _delay_ms(500);
    }
    return 0;
}
