#include "ssd1306.h"
#include "i2c.h"
#include <util/delay.h>
#include <math.h>
#include <stdlib.h>

void ssd1306_init(void)
{
    _delay_ms(100);
    i2c_init();
    ssd1306_start_command_frame();
    i2c_write(0xA8);
    i2c_write(0x3F);
    i2c_write(0xD3);
    i2c_write(0x00);
    i2c_write(0x40);
    i2c_write(0xA0);
    i2c_write(0xC0);
    i2c_write(0xDA);
    i2c_write(0x12);
    i2c_write(0x81);
    i2c_write(0x7F);
    i2c_write(0xA4);
    i2c_write(0xA6);
    i2c_write(0xD5);
    i2c_write(0x80);
    i2c_write(0x8D);
    i2c_write(0x14);
    i2c_write(0xAF);
    i2c_write(SET_MEMORY_ADDRESSING_MODE);
    i2c_write(0x00);
    i2c_write(SET_COLUMN_ADDRESS);
    i2c_write(0x00);
    i2c_write(0x7F);
    i2c_write(SET_PAGE_ADDRESS);
    i2c_write(0x00);
    i2c_write(0x07);
    ssd1306_stop_frame();
    ssd1306_start_data_frame();
    for (int i = 0; i < 1024; i++)
        i2c_write(0x00);
    ssd1306_stop_frame();
}

void ssd1306_command(char cmd)
{
    i2c_start();
    i2c_write(SLA_W(SSD1306_ADDRESS));
    i2c_write(0x00);
    i2c_write(cmd);
    i2c_stop();
    _delay_us(2);
}

void ssd1306_data(char data)
{
    i2c_start();
    i2c_write(SLA_W(SSD1306_ADDRESS));
    i2c_write(0x40);
    i2c_write(data);
    i2c_stop();
    _delay_us(2);
}

void ssd1306_start_command_frame(void)
{
    i2c_start();
    i2c_write(SLA_W(SSD1306_ADDRESS));
    i2c_write(0x00);
}

void ssd1306_start_data_frame(void)
{
    i2c_start();
    i2c_write(SLA_W(SSD1306_ADDRESS));
    i2c_write(0x40);
}

void ssd1306_stop_frame(void)
{
    i2c_stop();
    _delay_us(2);
}

void ssd1306_update_graphics(Graphics *g)
{
    ssd1306_start_data_frame();
    for (int i = 0; i < 1024; i++)
        i2c_write(g->buffer[i]);
    ssd1306_stop_frame();
}