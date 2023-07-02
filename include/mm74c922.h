/**
 * @file mm74c922.h
 * @author Iván Santiago
 * @date 07-01-2023 18:01
 * @brief Library to use a keypad decoder MM74C922
*/
#ifndef _MM74C922_H_
#define _MM74C922_H_
/**
 * Assigns a char value to a cell from keypad
 * @param r row of the cell
 * @param c column of the cell
 * @param value character to assign
*/
void mm74c922_map_cell(int r, int c, char value);
/**
 * Gets a character from a key
 * @param cell binary code in the output of the encoder
 * @return a character from any cell of the keypad
*/
char mm74c922_getch(int cell);
#endif