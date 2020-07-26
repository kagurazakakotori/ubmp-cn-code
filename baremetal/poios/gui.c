#include "efi.h"
#include "common.h"
#include "file.h"
#include "graphics.h"
#include "shell.h"
#include "gui.h"

#define WIDTH_PER_CH       8
#define HEIGHT_PER_CH      20
#define CURSOR_WIDTH       4
#define CURSOR_HEIGHT      4
#define EXIT_BUTTON_WIDTH  20
#define EXIT_BUTTON_HEIGHT 20

struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL cursor_tmp[CURSOR_HEIGHT][CURSOR_WIDTH] =
    {
        {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};
int cursor_old_x;
int cursor_old_y;
struct FILE rect_exit_button;

void draw_cursor(int x, int y)
{
    int i, j;
    for (i = 0; i < CURSOR_HEIGHT; i++)
        for (j = 0; j < CURSOR_WIDTH; j++)
            if ((i * j) < CURSOR_WIDTH)
                draw_pixel(x + j, y + i, white);
}

void save_cursor_area(int x, int y)
{
    int i, j;
    for (i = 0; i < CURSOR_HEIGHT; i++) {
        for (j = 0; j < CURSOR_WIDTH; j++) {
            if ((i * j) < CURSOR_WIDTH) {
                cursor_tmp[i][j] = get_pixel(x + j, y + i);
                cursor_tmp[i][j].Reserved = 0xff;
            }
        }
    }
}

void load_cursor_area(int x, int y)
{
    int i, j;
    for (i = 0; i < CURSOR_HEIGHT; i++)
        for (j = 0; j < CURSOR_WIDTH; j++)
            if ((i * j) < CURSOR_WIDTH)
                draw_pixel(x + j, y + i, cursor_tmp[i][j]);
}

void put_cursor(int x, int y)
{
    if (cursor_tmp[0][0].Reserved)
        load_cursor_area(cursor_old_x, cursor_old_y);

    save_cursor_area(x, y);

    draw_cursor(x, y);

    cursor_old_x = x;
    cursor_old_y = y;
}

void put_exit_button(void)
{
    unsigned int hr = GOP->Mode->Info->HorizontalResolution;
    unsigned int x;

    rect_exit_button.rect.x = hr - EXIT_BUTTON_WIDTH;
    rect_exit_button.rect.y = 0;
    rect_exit_button.rect.w = EXIT_BUTTON_WIDTH;
    rect_exit_button.rect.h = EXIT_BUTTON_HEIGHT;
    rect_exit_button.is_highlight = FALSE;
    draw_rect(rect_exit_button.rect, white);

    /* 绘制按钮中的X图案 */
    for (x = 3; x < rect_exit_button.rect.w - 3; x++) {
        draw_pixel(x + rect_exit_button.rect.x, x, white);
        draw_pixel(x + rect_exit_button.rect.x, rect_exit_button.rect.w - x, white);
    }
}

unsigned char update_exit_button(int px, int py, unsigned char is_clicked)
{
    unsigned char is_exit = FALSE;

    if (is_in_rect(px, py, rect_exit_button.rect)) {
        if (!rect_exit_button.is_highlight) {
            draw_rect(rect_exit_button.rect, yellow);
            rect_exit_button.is_highlight = TRUE;
        }
        if (is_clicked)
            is_exit = TRUE;
    } else {
        if (rect_exit_button.is_highlight) {
            draw_rect(rect_exit_button.rect, white);
            rect_exit_button.is_highlight = FALSE;
        }
    }

    return is_exit;
}

int ls_gui(void)
{
    int file_num;
    struct RECT t;
    int idx;

    ST->ConOut->ClearScreen(ST->ConOut);

    file_num = ls();

    t.x = 0;
    t.y = 0;
    t.w = (MAX_FILE_NAME_LEN - 1) * WIDTH_PER_CH;
    t.h = HEIGHT_PER_CH;
    for (idx = 0; idx < file_num; idx++) {
        file_list[idx].rect.x = t.x;
        file_list[idx].rect.y = t.y;
        file_list[idx].rect.w = t.w;
        file_list[idx].rect.h = t.h;
        draw_rect(file_list[idx].rect, white);
        t.x += file_list[idx].rect.w + WIDTH_PER_CH;

        file_list[idx].is_highlight = FALSE;
    }

    return file_num;
}

void cat_gui(unsigned short *file_name)
{
    ST->ConOut->ClearScreen(ST->ConOut);

    cat(file_name);

    while (getc() != SC_ESC)
        ;
}

void gui(void)
{
    unsigned long long status;
    struct EFI_SIMPLE_POINTER_STATE s;
    int px = 0, py = 0;
    unsigned long long waitidx;
    int file_num;
    int idx;
    unsigned char prev_lb = FALSE;
    unsigned char prev_rb = FALSE, executed_rb;
    unsigned char is_exit = FALSE;

    SPP->Reset(SPP, FALSE);
    file_num = ls_gui();
    put_exit_button();

    while (!is_exit) {
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

            /* 清除“已处理过右键事件”标志 */
            executed_rb = FALSE;

            /* 处理文件图标 */
            for (idx = 0; idx < file_num; idx++) {
                if (is_in_rect(px, py, file_list[idx].rect)) {
                    if (!file_list[idx].is_highlight) {
                        draw_rect(file_list[idx].rect, yellow);
                        file_list[idx].is_highlight = TRUE;
                    }
                    if (prev_lb && !s.LeftButton) {
                        if (file_list[idx].name[0] != L'i')
                            cat_gui(file_list[idx].name);
                        else
                            view(file_list[idx].name, IMG_WIDTH, IMG_HEIGHT);
                        file_num = ls_gui();
                        put_exit_button();
                    }
                    if (prev_rb && !s.RightButton) {
                        edit(file_list[idx].name);
                        file_num = ls_gui();
                        put_exit_button();
                        executed_rb = TRUE;
                    }
                } else {
                    if (file_list[idx].is_highlight) {
                        draw_rect(file_list[idx].rect, white);
                        file_list[idx].is_highlight = FALSE;
                    }
                }
            }

            /* 新建文件 */
            if ((prev_rb && !s.RightButton) && !executed_rb) {
                /* 处理文件图标外的右键单击事件 */
                dialogue_get_filename(file_num);
                edit(file_list[file_num].name);
                ST->ConOut->ClearScreen(ST->ConOut);
                file_num = ls_gui();
                put_exit_button();
            }

            /* 更新退出按钮状态 */
            is_exit = update_exit_button(px, py, prev_lb && !s.LeftButton);

            /* 保存鼠标按键状态 */
            prev_lb = s.LeftButton;
            prev_rb = s.RightButton;
        }
    }
}
