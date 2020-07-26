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
        } else {
            Print(L"Command not found.\r\n");
        }
    }
}
