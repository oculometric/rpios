#include <stdint.h>
#include <malloc.h>
#include <stdio.h>

#pragma pack(1)
typedef struct FRAMEBUFFER {
    uint32_t physical_width;
    uint32_t physical_height;
    uint32_t virtual_width;
    uint32_t virutal_height;
    uint32_t pitch;
    uint32_t depth;
    uint32_t virtual_x_offset;
    uint32_t virtual_y_offset;
    uint32_t framebuffer_address;
    uint32_t framebuffer_size;
} FRAMEBUFFER;

int main () {
    void *head = malloc (sizeof(FRAMEBUFFER));


    *(FRAMEBUFFER *)((void *)head) = (FRAMEBUFFER){
        640,
        480,
        640,
        480,
        0,
        24,
        0,
        0,
        0,
        0
    };

    FRAMEBUFFER *buf = (FRAMEBUFFER *)head;

    printf ("done");
    printf ("%d", (uint32_t)head);
    printf ("%d", (uint64_t)head);
}