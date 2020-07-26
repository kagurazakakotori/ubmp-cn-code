#include "common.h"
#include "shell.h"

#define MAX_COMMAND_LEN 100

void shell(void)
{
    unsigned short com[MAX_COMMAND_LEN];

    while (TRUE) {
        puts(L"poiOS> ");
        if (gets(com, MAX_COMMAND_LEN) <= 0)
            continue;

        if (!strcmp(L"hello", com))
            puts(L"Hello UEFI!\r\n");
        else
            puts(L"Command not found.\r\n");
    }
}
