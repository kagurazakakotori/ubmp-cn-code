#ifndef _GUI_H_
#define _GUI_H_

#include <efi.h>
#include <efilib.h>
#include "graphics.h"
#include "file.h"
#include "keyevent.h"
#include "shell.h"

#define CHAR_WIDTH  8
#define CHAR_HEIGHT 20

struct Cursor {
    INT32 x;
    INT32 y;
    INT32 saved_x;
    INT32 saved_y;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL saved_pixel;
};

void gui();
void update_cursor_position(EFI_SIMPLE_POINTER_STATE *state);
void put_cursor();
void ls_gui();
void cat_gui(CHAR16 *filename);

#endif
