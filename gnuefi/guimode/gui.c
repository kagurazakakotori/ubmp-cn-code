#include "gui.h"

void gui()
{
    struct Rect rect = {10, 10, 20, 20};

    uefi_call_wrapper(ST->ConOut->ClearScreen, 1, ST->ConOut);

    /* 绘制一个矩形图标 */
    draw_rect(rect, white);

    while (TRUE)
        ;
}
