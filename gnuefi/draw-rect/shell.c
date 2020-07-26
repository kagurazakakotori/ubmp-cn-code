#include "shell.h"

void shell()
{
    CHAR16 command[MAX_COMMAND_LEN];

    while (TRUE) {
        Input(L"poiOS> ", command, MAX_COMMAND_LEN);
        Print(L"\r\n");

        if (StrLen(command) == 0) {
            continue;
        }

        if (!StrCmp(L"hello", command)) {
            Print(L"Hello UEFI!\r\n");
        } else if (!StrCmp(L"rect", command)) {
            rect();
        } else {
            Print(L"Command not found.\r\n");
        }
    }
}

void rect()
{
    struct Rect rect = {10, 10, 100, 200};
    draw_rect(rect, white);
}
