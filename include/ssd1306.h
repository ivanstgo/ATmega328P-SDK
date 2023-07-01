#ifndef SSD1306_H
#include "graphics.h"

#define SSD1306_H
/**
 * SSD1306 i2c address
 */
#define SSD1306_ADDRESS 0x3C

/**
 * Two byte command to select 1 out of 256 contrast steps.
 */
#define SET_CONTRAST_CONTROL 0x81

/**
 * Entire display on command.
 * X0 = 0 output follows RAM content.
 * X0 = 1 Output ignores RAM content.
 */
#define ENTIRE_DISPLAY_ON(X0) (0xA4 | ((X0) ? 0x01 : 0x00))

/**
 * X0 = 0 normal display (0 in RAM off in display panel).
 * X0 = 1 inverse display (0 in RAM on in display panel).
 */
#define SET_NORMAL_INVERSE_DISPLAY(X0) (0xA6 | ((X0) ? 0x01 : 0x00))

/**
 * X0 = 0 display off (sleep mode)
 * X0 = 1 display on in normal mode
 */
#define SET_DISPLAY_ON_OFF(X0) (0xAE | ((X0) ? 0x01 : 0x00))

/**
 * X0 = 0 right horizontal scroll
 * X0 = 1 left horizontal scroll
 * A[7:0] dummy byte 0x00
 * B[2:0] define start page address
 * C[2:0] set time interval between each scroll step in terms of frame frequency
 * 0 5   frames
 * 1 64  frames
 * 2 128 frames
 * 3 256 frames
 * 4 3   frames
 * 5 4   frames
 * 6 25  frames
 * 7 2   frames
 * D[2:0] define end page address D >= b
 * E[7:0] dummy byte 0x00
 * F[7:0] dummy byte 0xFF
 */
#define CONTINUOS_HORIZONTAL_SCROLL_SETUP(X0) (0x26 | ((X0) ? 0x01 : 0x00))

/**
 * X1X0 = 01 vertical and right horizontal scroll
 * X1X0 = 10 vertical and left horizontal scroll
 * A[7:0] dummy byte 0x00
 * B[2:0] define start page address
 * C[2:0] Set time interval between each scroll step in terms of frame frequency
 * 0 5   frames
 * 1 64  frames
 * 2 128 frames
 * 3 256 frames
 * 4 3   frames
 * 5 4   frames
 * 6 25  frames
 * 7 2   frames
 * D[2:0] define end page address
 * E[5:0] vertical scrolling offset
 */
#define CONTINUOS_VERTICAL_AND_HORIZONTAL_SCROLL_SETUP(X1, X0) (0x29 | ((X1) ? 0x02 : 0x00) | ((X0) ? 0x01 : 0x00))

/**
 *  Stop scrolling that is configured by command 26h/27h/29h/2Ah.
 */
#define DEACTIVATE_SCROLL 0x2E

/**
 * Start scrolling that is configured by the scrolling setup
 * commands :26h/27h/29h/2Ah.
 * P. 29
 */
#define ACTIVATE_SCROLL 0x2F

/**
 * Set vertical scroll area
 * A[5:0] set No. of rows in top fixed area
 * B[6:0] set No. of rows in scroll area
 */
#define SET_VERTICAL_SCROLL_AREA 0xA3

/**
 * Two byte command to set memory addressing mode
 * A[1:0]
 * 0 horizontal addressing mode
 * 1 vertical addressing mode
 * 2 page addressing mode (RESET)
 * 3 invalid
 * P. 30
 */
#define SET_MEMORY_ADDRESSING_MODE 0x20

/**
 * Set column address
 * A[6:0] column start address, range: 0-127 (RESET=0)
 * B[6:0] column end address, range: 0-127 (RESET=127)
*/
#define SET_COLUMN_ADDRESS 0x21

/**
 * Setup page start and end address
 * A[2:0] page start address, range: 0-7 (RESET = 0)
 * B[2:0] page end address, range: 0-7 (RESET = 7)
*/
#define SET_PAGE_ADDRESS 0x22

void ssd1306_init(void);
void ssd1306_command(char cmd);
void ssd1306_data(char data);
void ssd1306_update_graphics(Graphics *g);
void ssd1306_start_data_frame(void);
void ssd1306_start_command_frame(void);
void ssd1306_stop_frame(void);
#endif