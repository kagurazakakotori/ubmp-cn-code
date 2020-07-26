#include "common.h"
#include "graphics.h"
#include "shell.h"

#define MAX_COMMAND_LEN 100

void shell(void)
{
    unsigned short com[MAX_COMMAND_LEN];
    struct RECT r = {10, 10, 100, 200};

    while (TRUE) {
        puts(L"poiOS> ");
        if (gets(com, MAX_COMMAND_LEN) <= 0)
            continue;

        if (!strcmp(L"hello", com))
            puts(L"Hello UEFI!\r\n");
        else if (!strcmp(L"rect", com))
            draw_rect(r, white);
        else
            puts(L"Command not found.\r\n");
    }
}
