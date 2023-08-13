#include <avr/io.h>
#include "ports.h"

void arduino_pin_set_dir(ArduinoPin arduino_pin, Direction dir)
{
    if (arduino_pin < D8)
    {
        portD_set_dir((PinNumber)arduino_pin, dir);
    }
    else if (arduino_pin >= D8 && arduino_pin < D14)
    {
        portB_set_dir((PinNumber)(arduino_pin - 8), dir);
    }
    else
    {
        portC_set_dir((PinNumber)(arduino_pin - 14), dir);
    }
}

void arduino_pin_write(ArduinoPin arduino_pin, unsigned char value)
{
    if (arduino_pin < D8)
    {
        portD_write((PinNumber)arduino_pin, value);
    }
    else if (arduino_pin >= D8 && arduino_pin < D14)
    {
        portB_write((PinNumber)(arduino_pin - 8), value);
    }
    else
    {
        portC_write((PinNumber)(arduino_pin - 14), value);
    }
}

void arduino_pin_toggle(ArduinoPin arduino_pin)
{
    if (arduino_pin < D8)
    {
        portD_toggle((PinNumber)arduino_pin);
    }
    else if (arduino_pin >= D8 && arduino_pin < D14)
    {
        portB_toggle((PinNumber)(arduino_pin - 8));
    }
    else
    {
        portC_toggle((PinNumber)(arduino_pin - 14));
    }
}

unsigned char arduino_pin_read(ArduinoPin arduino_pin)
{
    if (arduino_pin < D8)
    {
        return portD_read((PinNumber)arduino_pin);
    }
    else if (arduino_pin >= D8 && arduino_pin < D14)
    {
        return portB_read((PinNumber)(arduino_pin - 8));
    }
    return portC_read((PinNumber)(arduino_pin - 14));
}
