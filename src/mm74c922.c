#include "mm74c922.h"

char keymap[16] = {'1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8', '9', 'C', '*', '0', '#', 'D'};

void mm74c922_map_cell(int r, int c, char value)
{
    keymap[r * 4 + c] = value;
}

char mm74c922_getch(int cell)
{
    return keymap[cell];
}