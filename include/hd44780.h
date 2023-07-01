#ifndef HD_44780_H
#define HD_44780_H
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

void lcd_init(unsigned char function_set, unsigned char display_control, unsigned char entry_mode);
void lcd_command(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_print_string(const char *string);
void lcd_generate_character(unsigned char n, const char *pattern);
void lcd_set_position(unsigned char r, unsigned char c);
#endif