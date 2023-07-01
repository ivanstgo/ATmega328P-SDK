#include "mm74c922.h"

char keymap[16] = {'1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8', '9', 'C', '*', '0', '#', 'D'};

/**
 * Assigns a char value to a cell from keypad
 * @param r row of the cell
 * @param c column of the cell
 * @param value character to assign
*/
void mm74c922_map_cell(int r, int c, char value)
{
    keymap[r * 4 + c] = value;
}

/**
 * Gets a character from a key
 * @param cell binary code in the output of the encoder
 * @return a character from any cell of the keypad
*/
char mm74c922_getch(int cell)
{
    return keymap[cell];
}