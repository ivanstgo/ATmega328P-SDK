/**
 * @file graphics.h
 * @author Iván Santiago
 * @date 07-01-2023 17:45
 * @brief Library for drawing graphic primitives on OLED display SSD1306
*/
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

typedef struct graphics
{
    unsigned char buffer[1024];
} Graphics;
/**
 * Draws a string into graphics buffer
 * @param g graphics buffer
 * @param string texto to draw
 * @param r row (range[0-7])
 * @param c column (range[0-21]);
 */
void draw_text(Graphics *g, const char *string, unsigned int r, unsigned int c);
/**
 * Draw a bitmap into graphics buffer
 * @param g graphics buffer
 * @param image bitmap to draw
 * @param r row (range[0-7])
 * @param x column (range[0-127]);
 */
void draw_image(Graphics *g, const unsigned char *image, unsigned int w, unsigned int length, unsigned int r, unsigned int x);
/**
 * Clean the graphics buffer
 * @param g graphics buffer
 */
void clear_graphics(Graphics *g);
/**
 * Draws a pixel into the display
 * @param g graphics buffer
 * @param x horizontal position
 * @param y vertical position
 */
void draw_pixel(Graphics *g, unsigned int x, unsigned int y);
/**
 * Draws a line using the Bresenham algorithm
 * @param g graphics buffer
 * @param x1 start x
 * @param y1 start y
 * @param x2 end x
 * @param y2 end y
 */
void draw_line(Graphics *g, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
/**
 * Draw a circle using the midpoint algorithm
 * @param g graphics buffer
 * @param x centre x
 * @param y centre y
 * @param r radius
 */
void draw_circle(Graphics *g, unsigned int xc, unsigned int yc, unsigned int r);
/**
 * Draws a triangle
 * @param g graphics buffer
 * @param x1 first point x
 * @param y1 first point y
 * @param x2 second point x
 * @param y2 second point y
 * @param x3 third point x
 * @param y3 third point y
 */
void draw_triangle(Graphics *g, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int x3, unsigned int y3);
/**
 * Draws a rectangle
 * @param g graphics buffer
 * @param x top left corner x
 * @param y top left corner y
 * @param w width
 * @param h height
 */
void draw_rectangle(Graphics *g, unsigned int x, unsigned int y, unsigned int w, unsigned int h);
/**
 * Draws a polygon
 * @param g graphics buffer
 * @param x an array that contains x components of the points
 * @param y an array that contains y components of the points
 * @param n number of points
 */
void draw_polygon(Graphics *g, unsigned int *x, unsigned int *y, unsigned int n);
/**
 * Connects an array of point by lines
 * @param g graphics buffer
 * @param x an array that contains x components of the points
 * @param y an array that contains y components of the points
 * @param n number of points
 */
void draw_polyline(Graphics *g, unsigned int *x, unsigned int *y, unsigned int n);
#endif