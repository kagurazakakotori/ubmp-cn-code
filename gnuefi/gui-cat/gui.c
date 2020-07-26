#include "gui.h"

static struct Cursor cursor = {
    .saved_x = -1,
    .saved_y = -1,
};

void gui()
{
    EFI_SIMPLE_POINTER_STATE state;
    BOOLEAN saved_leftbtn = FALSE;

    uefi_call_wrapper(ST->ConOut->SetMode, 2, ST->ConOut, 2); // fix text position for ovmf
    uefi_call_wrapper(ST->ConOut->ClearScreen, 1, ST->ConOut);
    uefi_call_wrapper(SPP->Reset, 2, SPP, FALSE);
    ls_gui();

    while (TRUE) {
        WaitForSingleEvent(SPP->WaitForInput, 0);

        if (!uefi_call_wrapper(SPP->GetState, 2, SPP, &state)) {
            /* 更新鼠标指针位置 */
            update_cursor_position(&state);
            /* 绘制鼠标指针 */
            put_cursor();
            /* 处理文件图标 */
            for (UINTN i = 0; i < filelist.file_count; i++) {
                if (is_in_rect(cursor.x, cursor.y, filelist.files[i].icon)) {
                    if (!filelist.files[i].highlighted) {
                        draw_rect(filelist.files[i].icon, yellow);
                        filelist.files[i].highlighted = TRUE;
                    }
                    if (saved_leftbtn && !state.LeftButton) {
                        cat_gui(filelist.files[i].name);
                        ls_gui();
                    }
                } else {
                    if (filelist.files[i].highlighted) {
                        draw_rect(filelist.files[i].icon, white);
                        filelist.files[i].highlighted = FALSE;
                    }
                }
            }
            /* 保存鼠标左键状态 */
            saved_leftbtn = state.LeftButton;
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

void ls_gui()
{
    struct Rect temp = {
        .x = 0,
        .y = 0,
        .height = CHAR_HEIGHT,
        .width = (MAX_FILENAME_LEN - 1) * CHAR_WIDTH,
    };

    uefi_call_wrapper(ST->ConOut->ClearScreen, 1, ST->ConOut);

    ls();
    for (UINTN i = 0; i < filelist.file_count; i++) {
        filelist.files[i].highlighted = FALSE;
        CopyMem(&(filelist.files[i].icon), &temp, sizeof(struct Rect));

        draw_rect(filelist.files[i].icon, white);
        temp.x += MAX_FILENAME_LEN * CHAR_WIDTH;
    }
}

void cat_gui(CHAR16 *filename)
{
    uefi_call_wrapper(ST->ConOut->ClearScreen, 1, ST->ConOut);
    cat(filename);
    wait_key_pressed(&ESC_KEY);
}
