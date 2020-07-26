#include "graphics.h"

const EFI_GRAPHICS_OUTPUT_BLT_PIXEL white = {0xff, 0xff, 0xff, 0x00};
const EFI_GRAPHICS_OUTPUT_BLT_PIXEL yellow = {0x00, 0xff, 0xff, 0x00};

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

EFI_GRAPHICS_OUTPUT_BLT_PIXEL get_pixel(UINTN x, UINTN y)
{
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL result;
    uefi_call_wrapper(GOP->Blt, 10, GOP, &result, EfiBltVideoToBltBuffer, x, y, 0, 0, 1, 1, 0);
    return result;
}

BOOLEAN is_in_rect(UINTN x, UINTN y, struct Rect rect)
{
    if (x < rect.x || x >= rect.x + rect.width || y < rect.y || y >= rect.y + rect.height) {
        return FALSE;
    }
    return TRUE;
}
