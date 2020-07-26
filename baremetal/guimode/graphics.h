#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "efi.h"

struct RECT {
    unsigned int x, y;
    unsigned int w, h;
};

extern const struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL white;

void draw_pixel(unsigned int x, unsigned int y, struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL color);
void draw_rect(struct RECT r, struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL c);

#endif
