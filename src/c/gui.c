#include "gui.h"
#include "uart.h"
#include "math.h"
#include "mem.h"

void draw_pixel (FRAMEBUFFER_DATA *fbd, int x, int y, uint32_t col) {
    if (x < 0 || x >= fbd->virtual_width || y < 0 || y >= fbd->virtual_height) return;
    char *pixelbuf = (char *)(fbd->framebuffer_address + fbd->framebuffer_size);
    uint32_t offset = (x*(fbd->depth/8))+(y*(fbd->pitch));
    pixelbuf[offset] = col & 0xFF;
    pixelbuf[offset+1] = (col >> 8) & 0xFF;
    pixelbuf[offset+2] = (col >> 16) & 0xFF;
}

void draw_element (FRAMEBUFFER_DATA *fbd, graphics_element* el) {
    char *pixelbuf = (char *)(fbd->framebuffer_address + fbd->framebuffer_size);
    switch (el->shape)
    {
    case graphics_rectangle:
        for (int y = el->y; y < el->y+el->height; y++) {
            for (int x = el->x; x < el->x+el->width; x++) {
                if (x < 0 || x >= fbd->virtual_width || y < 0 || y >= fbd->virtual_height) continue;
                uint32_t offset = (x*(fbd->depth/8))+(y*(fbd->pitch));
                pixelbuf[offset] = el->colour & 0xFF;
                pixelbuf[offset+1] = (el->colour >> 8) & 0xFF;
                pixelbuf[offset+2] = (el->colour >> 16) & 0xFF;
            }
        }
        break;
    case graphics_circle:
        int ar = el->width/2;
        int br = el->height/2;
        int a = el->x+(ar);
        int b = el->y+(br);
        float theta = 0;
        float step = 0.5/br;
        while (theta < MATH_PI) {
            int xp = a+(ar*cos(theta*2));
            int xn = (2*a)-xp;
            int y = b-(br*sin(theta*2));
            for (int x = xn; x <= xp; x++) {
                if (x < 0 || x >= fbd->virtual_width || y < 0 || y >= fbd->virtual_height) continue;
                uint32_t offset = (x*(fbd->depth/8))+(y*(fbd->pitch));
                pixelbuf[offset] = el->colour & 0xFF;
                pixelbuf[offset+1] = (el->colour >> 8) & 0xFF;
                pixelbuf[offset+2] = (el->colour >> 16) & 0xFF;
            }
            theta += step;
        }
        break;
    
    default:
        break;
    }
}

void center_element_at(graphics_element* el, int cx, int cy, int sx, int sy) {
    int wo2 = sx/2;
    int ho2 = sy/2;
    el->x = cx-wo2;
    el->width = sx;
    el->y = cy-ho2;
    el->height = sy;
}

uint32_t colour_from_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return (a << 24) | (b << 16) | (g << 8) | r;
}

void draw_gui(FRAMEBUFFER_DATA* fbd) {
    graphics_element background[1];
    background->shape = graphics_rectangle;
    background->colour = colour_from_rgba(50, 50, 50, 0);
    background->x = 0;
    background->y = 0;
    background->width = fbd->virtual_width;
    background->height = fbd->virtual_height;

    graphics_element rect[1];
    rect->shape = graphics_rectangle;
    rect->colour = colour_from_rgba(255, 128, 255, 0);
    center_element_at (rect, fbd->virtual_width/2, fbd->virtual_height/2, 400, 400);

    draw_element (fbd, background);
    draw_element (fbd, rect);

    for (int i = 0; i < 500; i++) {
        draw_pixel (fbd, i, i, colour_from_rgba(i%255, 0, 0, 0));
    }
}

void flip(FRAMEBUFFER_DATA* fbd) {
    copy_mem (fbd->framebuffer_address + fbd->framebuffer_size, fbd->framebuffer_address, fbd->framebuffer_size);
}