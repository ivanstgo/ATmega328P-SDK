#include "hd44780.h"
#include <util/delay.h>
#include <math.h>
#include "i2c.h"

/**
 * Sets interface to be 4 bits long and configures LCD options.
 * @param function_set specify the number of display lines and character font.
 * @param display_control specify the display, cursor and blinking enable.
 * @param entry_mode specify the entry mode.
 */
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

/**
 * Sends a command to LCD
 * @param cmd command to execute
*/
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

/**
 * Displays a character in the display
 * @param data the character to display
*/
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

/**
 * Displays a character string in the display
 * @param string character string to show
 */
void lcd_print_string(const char *string)
{
    int i = 0;
    while (*(string + i))
    {
        lcd_data(*(string + i));
        i++;
    }
}

/**
 * Stores a custom character in the CGRAM
 * @param n custom character code in DDRAM. Range [0x00-0x07]
 * @param pattern the data of pattern (5x8 dots)
*/
void lcd_generate_character(unsigned char n, const char *pattern)
{
    lcd_command(SET_CGRAM_ADDRESS(n << 3));
    for (int i = 0; i < 8; i ++)
    {
        lcd_data(*(pattern + i));
    }
    lcd_command(SET_DDRAM_ADDRESS(0x00));
}

/**
 * Set the cursor position
 * @param r row
 * @param c column
*/
void lcd_set_position(unsigned char r, unsigned char c)
{
    lcd_command(SET_DDRAM_ADDRESS(r > 0 ? 0x40 + c : c));
}