#include "efi.h"
#include "common.h"

void efi_main(void *ImageHandle __attribute__((unused)), struct EFI_SYSTEM_TABLE *SystemTable)
{
    efi_init(SystemTable);
    ST->ConOut->ClearScreen(ST->ConOut);

    /* test1 */
    if (!ST->ConOut->TestString(ST->ConOut, L"Hello"))
        puts(L"test1: success\r\n");
    else
        puts(L"test1: fail\r\n");

    /* test2 */
    if (!ST->ConOut->TestString(ST->ConOut, L"你好"))
        puts(L"test2: success\r\n");
    else
        puts(L"test2: fail\r\n");

    /* test3 */
    if (!ST->ConOut->TestString(ST->ConOut, L"Hello, 你好"))
        puts(L"test3: success\r\n");
    else
        puts(L"test3: fail\r\n");

    while (TRUE)
        ;
}
