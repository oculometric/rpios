#ifndef GUI_H
#define GUI_H

#include <stdint.h>

#pragma pack(1)
typedef struct FRAMEBUFFER_DATA {
    uint32_t physical_width;
    uint32_t physical_height;
    uint32_t virtual_width;
    uint32_t virtual_height;
    uint32_t pitch;
    uint32_t depth;
    uint32_t virtual_x_offset;
    uint32_t virtual_y_offset;
    uint32_t framebuffer_address;
    uint32_t framebuffer_size;
} FRAMEBUFFER_DATA;

enum graphics_shape {
    graphics_rectangle = 0,
    graphics_circle = 1,
    graphics_diamond = 2
};

typedef struct graphics_element {
    int x;
    int y;
    int width;
    int height;
    uint32_t colour;
    uint8_t shape;

} graphics_element;

void draw_element(FRAMEBUFFER_DATA*, graphics_element*);
void draw_pixel(FRAMEBUFFER_DATA*, int, int, uint32_t);
void draw_gui(FRAMEBUFFER_DATA*);
void center_element_at(graphics_element*, int, int, int, int);
uint32_t colour_from_rgba(uint8_t, uint8_t, uint8_t, uint8_t);
void flip(FRAMEBUFFER_DATA*);

#endif