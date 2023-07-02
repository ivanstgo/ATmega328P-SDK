/**
 * @file hd44780.h
 * @author Iván Santiago
 * @date 07-01-2023 17:55
 * @brief Library to use a LCD display HD44780 using I2C
*/
#ifndef _HD44780_H_
#define _HD44780_H_
/**
 * PCF8574 address
*/
#define PCF8574_ADDRESS 0x27
/**
 * I2C frame format
 * D7 D6 D5 D4 BL EN RW RS
*/
#define LCD_RS 0x01
#define LCD_RW 0x02
#define LCD_EN 0x04
#define LCD_BACKLIGHT 0x08

/**
 * When N is 0 selects one display lines.
 * When N is 1 selects two display lines and 5 x 8 dots font.
 * When F is 0 selects 5 x 8 dots font.
 * When F is 1 selects 5 x 10 dots font.
*/
#define FUNCTION_SET(N, F) (0x20 | ((N)? 0x08 : 0x00) | ((F)? 0x04 : 0x00))

/**
 * When D is 1 the display is on.
 * When C is 1 the cursor is displayed.
 * When B is 1 the blinking is enabled.
*/
#define DISPLAY_ON_OFF_CONTROL(D, C, B) (0x08 | ((D)? 0x04 : 0x00) | ((C)? 0x02 : 0x00) | ((B)? 0x01 : 0x00))

/**
 * When ID is 0 decrements.
 * When ID is 1 increments.
 * When S is 1 and ID is 0 the entire display shifts to right.
 * When S is 1 and ID is 1 the entire display shifts to left.
*/
#define ENTRY_MODE_SET(ID, S) (0x04 | ((ID)? 0x02 : 0x00) | ((S)? 0x01 : 0x00))

/**
 * Instruction to clear display
*/
#define CLEAR_DISPLAY 0x01

/**
 * Instruction to return home
*/
#define RETURN_HOME 0x02

/**
 * S/R = 0 R/L = 0  Shifts the cursor position to the left.
 * S/R = 0 R/L = 1  Shifts the cursor position to the right.
 * S/R = 1 R/L = 0  Shifts the entire display to the left.
 * S/R = 1 R/L = 1  Shifts the entire display to the right.
*/
#define CURSOR_OR_DISPLAY_SHIFT(SR, RL) (0x10 | ((SR)? 0x08 : 0x00) | ((RL)? 0x04 : 0x00))

/**
 * Sets CGRAM address
*/
#define SET_CGRAM_ADDRESS(A) (0x40 | ((A) & 0x3F))

/**
 * Sets DDRAM address
 * When N is 0 (1-line display), AAAAAAA can be 0x00 to 0x4F.
 * When N is 1 (2-line display), AAAAAAA can be 0x00 to 0x27 for the first line,
 * and 0x40 to 0x67 for the second line.
*/
#define SET_DDRAM_ADDRESS(A) (0x80 | ((A) & 0x7F))
/**
 * Sets interface to be 4 bits long and configures LCD options.
 * @param function_set specify the number of display lines and character font.
 * @param display_control specify the display, cursor and blinking enable.
 * @param entry_mode specify the entry mode.
 */
void lcd_init(unsigned char function_set, unsigned char display_control, unsigned char entry_mode);
/**
 * Sends a command to LCD
 * @param cmd command to execute
*/
void lcd_command(unsigned char cmd);
/**
 * Displays a character in the display
 * @param data the character to display
*/
void lcd_data(unsigned char data);
/**
 * Displays a character string in the display
 * @param string character string to show
 */
void lcd_print_string(const char *string);
/**
 * Stores a custom character in the CGRAM
 * @param n custom character code in DDRAM. Range [0x00-0x07]
 * @param pattern the data of pattern (5x8 dots)
*/
void lcd_generate_character(unsigned char n, const char *pattern);
/**
 * Set the cursor position
 * @param r row
 * @param c column
*/
void lcd_set_position(unsigned char r, unsigned char c);
#endif