#include <avr/io.h>
#include <util/delay.h>
#include <io_pin.h>

int main(void)
{
    struct pin_config led_pin = {
        .pin = PIN_B5,
        .dir = OUTPUT,
        .pull_up = PULL_UP_DISABLED,
        .value = LOW
    };
    io_pin_configure(led_pin);

    while(1)
    {
        io_pin_toggle(led_pin.pin); 
        _delay_ms(500);
    }
    return 0;
}
