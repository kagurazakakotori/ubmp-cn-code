#include "efi.h"
#include "common.h"
#include "graphics.h"
#include "gui.h"

struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL cursor_tmp = {0, 0, 0, 0};
int cursor_old_x;
int cursor_old_y;

void draw_cursor(int x, int y)
{
    draw_pixel(x, y, white);
}

void save_cursor_area(int x, int y)
{
    cursor_tmp = get_pixel(x, y);
    cursor_tmp.Reserved = 0xff;
}

void load_cursor_area(int x, int y)
{
    draw_pixel(x, y, cursor_tmp);
}

void put_cursor(int x, int y)
{
    if (cursor_tmp.Reserved)
        load_cursor_area(cursor_old_x, cursor_old_y);

    save_cursor_area(x, y);

    draw_cursor(x, y);

    cursor_old_x = x;
    cursor_old_y = y;
}

void gui(void)
{
    struct RECT r = {10, 10, 20, 20};
    unsigned long long status;
    struct EFI_SIMPLE_POINTER_STATE s;
    int px = 0, py = 0;
    unsigned long long waitidx;
    unsigned char is_highlight = FALSE;

    ST->ConOut->ClearScreen(ST->ConOut);
    SPP->Reset(SPP, FALSE);

    /* 绘制一个矩形图标 */
    draw_rect(r, white);

    while (TRUE) {
        ST->BootServices->WaitForEvent(1, &(SPP->WaitForInput), &waitidx);
        status = SPP->GetState(SPP, &s);
        if (!status) {
            /* 更新鼠标指针位置 */
            px += s.RelativeMovementX >> 13;
            if (px < 0)
                px = 0;
            else if (GOP->Mode->Info->HorizontalResolution <= (unsigned int)px)
                px = GOP->Mode->Info->HorizontalResolution - 1;
            py += s.RelativeMovementY >> 13;
            if (py < 0)
                py = 0;
            else if (GOP->Mode->Info->VerticalResolution <= (unsigned int)py)
                py = GOP->Mode->Info->VerticalResolution - 1;

            /* 绘制鼠标指针 */
            put_cursor(px, py);

            /* 鼠标悬浮于矩形图标上时，高亮矩形图标 */
            if (is_in_rect(px, py, r)) {
                if (!is_highlight) {
                    draw_rect(r, yellow);
                    is_highlight = TRUE;
                }
            } else {
                if (is_highlight) {
                    draw_rect(r, white);
                    is_highlight = FALSE;
                }
            }
        }
    }
}
