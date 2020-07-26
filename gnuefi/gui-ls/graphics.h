#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <efi.h>
#include <efilib.h>
#include "global.h"

struct Rect {
    UINTN x, y;
    UINTN width, height;
};

extern const EFI_GRAPHICS_OUTPUT_BLT_PIXEL white;
extern const EFI_GRAPHICS_OUTPUT_BLT_PIXEL yellow;

void draw_pixel(UINTN x, UINTN y, EFI_GRAPHICS_OUTPUT_BLT_PIXEL color);
void draw_rect(struct Rect rect, EFI_GRAPHICS_OUTPUT_BLT_PIXEL color);
EFI_GRAPHICS_OUTPUT_BLT_PIXEL get_pixel(UINTN x, UINTN y);
BOOLEAN is_in_rect(UINTN x, UINTN y, struct Rect rect);

#endif
