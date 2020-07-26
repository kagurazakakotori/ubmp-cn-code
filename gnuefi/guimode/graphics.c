#include "graphics.h"

const EFI_GRAPHICS_OUTPUT_BLT_PIXEL white = {0xff, 0xff, 0xff, 0xff};

void draw_pixel(UINTN x, UINTN y, EFI_GRAPHICS_OUTPUT_BLT_PIXEL color)
{
    uefi_call_wrapper(GOP->Blt, 10, GOP, &color, EfiBltVideoFill, 0, 0, x, y, 1, 1, 0);
}

void draw_rect(struct Rect rect, EFI_GRAPHICS_OUTPUT_BLT_PIXEL color)
{
    uefi_call_wrapper(GOP->Blt, 10, GOP, &color, EfiBltVideoFill, 0, 0, rect.x, rect.y, rect.width, 1, 0);
    uefi_call_wrapper(GOP->Blt, 10, GOP, &color, EfiBltVideoFill, 0, 0, rect.x, rect.y, 1, rect.height, 0);
    uefi_call_wrapper(GOP->Blt, 10, GOP, &color, EfiBltVideoFill, 0, 0, rect.x, rect.y + rect.height - 1, rect.width, 1, 0);
    uefi_call_wrapper(GOP->Blt, 10, GOP, &color, EfiBltVideoFill, 0, 0, rect.x + rect.width - 1, rect.y, 1, rect.height, 0);
}
