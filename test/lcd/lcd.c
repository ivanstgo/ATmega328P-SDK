#include "io_pin.h"
#include "hd44780.h"
#include <util/delay.h>

int main(void)
{
    lcd_init(FUNCTION_SET(0, 1), DISPLAY_ON_OFF_CONTROL(1, 0, 0), ENTRY_MODE_SET(1, 0));
    struct pin_config sda_pin = {
        .pin = PIN_SDA,
        .dir = OUTPUT,
        .pull_up = PULL_UP_DISABLED,
        .value = LOW
    };
    struct pin_config scl_pin = {
        .pin = PIN_SCL,
        .dir = OUTPUT,
        .pull_up = PULL_UP_DISABLED,
        .value = LOW
    };
    io_pin_configure(sda_pin);
    io_pin_configure(scl_pin);
    lcd_print_string("Hello world!");
    uint8_t dir = 1;
    uint8_t count = 0;
    while (1){
        _delay_ms(800);
        lcd_command(CURSOR_OR_DISPLAY_SHIFT(1, dir));
        count++;
        if (count == 16)
        {
            dir = dir ? 0 : 1;
            count = 0;
        }
    };
    return 0;
}
