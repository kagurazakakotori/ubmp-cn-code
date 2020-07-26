#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <efi.h>
#include "global.h"

struct Rect {
    UINTN x, y;
    UINTN width, height;
};

extern const EFI_GRAPHICS_OUTPUT_BLT_PIXEL white;

void draw_pixel(UINTN x, UINTN y, EFI_GRAPHICS_OUTPUT_BLT_PIXEL color);
void draw_rect(struct Rect rect, EFI_GRAPHICS_OUTPUT_BLT_PIXEL color);

#endif
