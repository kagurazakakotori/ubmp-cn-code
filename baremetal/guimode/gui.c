#include "efi.h"
#include "common.h"
#include "graphics.h"
#include "gui.h"

void gui(void)
{
    struct RECT r = {10, 10, 20, 20};

    ST->ConOut->ClearScreen(ST->ConOut);

    /* 绘制一个矩形图标 */
    draw_rect(r, white);

    while (TRUE)
        ;
}
