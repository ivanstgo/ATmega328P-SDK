#ifndef GRAPHICS_H
#define GRAPHICS_H

typedef struct graphics
{
    unsigned char buffer[1024];
} Graphics;

void draw_text(Graphics *g, const char *string, unsigned int r, unsigned int c);
void draw_image(Graphics *g, const unsigned char *image, unsigned int w, unsigned int length, unsigned int r, unsigned int x);
void clear_graphics(Graphics *g);
void draw_pixel(Graphics *g, unsigned int x, unsigned int y);
void draw_line(Graphics *g, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void draw_circle(Graphics *g, unsigned int xc, unsigned int yc, unsigned int r);
void draw_triangle(Graphics *g, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int x3, unsigned int y3);
void draw_rectangle(Graphics *g, unsigned int x, unsigned int y, unsigned int w, unsigned int h);
void draw_polygon(Graphics *g, unsigned int *x, unsigned int *y, unsigned int n);
void draw_polyline(Graphics *g, unsigned int *x, unsigned int *y, unsigned int n);
#endif