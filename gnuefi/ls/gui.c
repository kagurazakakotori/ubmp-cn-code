#include "gui.h"

static struct Cursor cursor = {
    .saved_x = -1,
    .saved_y = -1,
};

void gui()
{
    struct Rect rect = {10, 10, 20, 20};
    EFI_SIMPLE_POINTER_STATE state;
    BOOLEAN icon_highlighted = FALSE;

    uefi_call_wrapper(ST->ConOut->ClearScreen, 1, ST->ConOut);
    uefi_call_wrapper(SPP->Reset, 2, SPP, FALSE);

    /* 绘制一个矩形图标 */
    draw_rect(rect, white);

    while (TRUE) {
        WaitForSingleEvent(SPP->WaitForInput, 0);

        if (!uefi_call_wrapper(SPP->GetState, 2, SPP, &state)) {
            /* 更新鼠标指针位置 */
            update_cursor_position(&state);
            /* 绘制鼠标指针 */
            put_cursor();
            /* 鼠标悬浮于矩形图标上时，高亮矩形图标 */
            if (is_in_rect(cursor.x, cursor.y, rect)) {
                if (!icon_highlighted) {
                    draw_rect(rect, yellow);
                    icon_highlighted = TRUE;
                }
            } else {
                if (icon_highlighted) {
                    draw_rect(rect, white);
                    icon_highlighted = FALSE;
                }
            }
        }
    }
}

void update_cursor_position(EFI_SIMPLE_POINTER_STATE *state)
{
    cursor.x += state->RelativeMovementX >> 13;
    cursor.y += state->RelativeMovementY >> 13;

    if (cursor.x < 0) {
        cursor.x = 0;
    } else if ((UINTN)cursor.x >= GOP->Mode->Info->HorizontalResolution) {
        cursor.x = GOP->Mode->Info->HorizontalResolution - 1;
    }

    if (cursor.y < 0) {
        cursor.y = 0;
    } else if ((UINTN)cursor.y >= GOP->Mode->Info->VerticalResolution) {
        cursor.y = GOP->Mode->Info->VerticalResolution - 1;
    }
}

void put_cursor()
{
    // restore saved pixel
    if (cursor.saved_x >= 0 && cursor.saved_y >= 0) {
        draw_pixel(cursor.saved_x, cursor.saved_y, cursor.saved_pixel);
    }

    // save cursor info
    cursor.saved_pixel = get_pixel(cursor.x, cursor.y);
    cursor.saved_x = cursor.x;
    cursor.saved_y = cursor.y;

    // draw cursor
    draw_pixel(cursor.x, cursor.y, white);
}
