#include "hd44780.h"
#include <util/delay.h>
#include <math.h>
#include "i2c.h"

void lcd_init(unsigned char function_set, unsigned char display_control, unsigned char entry_mode)
{
    i2c_init();
    _delay_ms(50);
    i2c_start();
    i2c_write(SLA_W(PCF8574_ADDRESS));
    i2c_write(0x30 | LCD_EN);
    i2c_write(0x30);
    _delay_ms(5);
    i2c_write(0x30 | LCD_EN);
    i2c_write(0x30);
    _delay_us(120);
    i2c_write(0x30 | LCD_EN);
    i2c_write(0x30);
    i2c_write(0x20 | LCD_EN);
    i2c_write(0x20);
    i2c_stop();
    lcd_command(function_set);
    lcd_command(CLEAR_DISPLAY);
    _delay_ms(5);
    lcd_command(display_control);
    lcd_command(entry_mode);
}

void lcd_command(unsigned char cmd)
{
    i2c_start();
    i2c_write(SLA_W(PCF8574_ADDRESS));
    i2c_write((cmd & 0xF0) | LCD_BACKLIGHT | LCD_EN);
    i2c_write((cmd & 0xF0) | LCD_BACKLIGHT);
    i2c_write((cmd & 0x0F) << 4 | LCD_BACKLIGHT | LCD_EN);
    i2c_write((cmd & 0x0F) << 4 | LCD_BACKLIGHT);
    i2c_stop();
    if (cmd == RETURN_HOME)
        _delay_ms(1.6);
    else
        _delay_us(40);
}

void lcd_data(unsigned char data)
{
    i2c_start();
    i2c_write(SLA_W(PCF8574_ADDRESS));
    i2c_write((data & 0xF0) | LCD_BACKLIGHT | LCD_EN | LCD_RS);
    i2c_write((data & 0xF0) | LCD_BACKLIGHT | LCD_RS);
    i2c_write((data & 0x0F) << 4 | LCD_BACKLIGHT | LCD_EN | LCD_RS);
    i2c_write((data & 0x0f) << 4 | LCD_BACKLIGHT | LCD_RS);
    i2c_stop();
    _delay_ms(1);   
}

void lcd_print_string(const char *string)
{
    int i = 0;
    while (*(string + i))
    {
        lcd_data(*(string + i));
        i++;
    }
}

void lcd_generate_character(unsigned char n, const char *pattern)
{
    lcd_command(SET_CGRAM_ADDRESS(n << 3));
    for (int i = 0; i < 8; i ++)
    {
        lcd_data(*(pattern + i));
    }
    lcd_command(SET_DDRAM_ADDRESS(0x00));
}

void lcd_set_position(unsigned char r, unsigned char c)
{
    lcd_command(SET_DDRAM_ADDRESS(r > 0 ? 0x40 + c : c));
}