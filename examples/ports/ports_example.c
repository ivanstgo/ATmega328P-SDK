#include <util/delay.h>
#include "ports.h"

int main(void)
{
    SET_OUTPUT_PORTB(5);
    for(;;)
    {
        TOGGLE_PORTB(5);
        _delay_ms(500);
    }
}