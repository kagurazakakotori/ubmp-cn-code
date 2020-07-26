#include "efi.h"
#include "common.h"

void efi_main(void *ImageHandle __attribute__((unused)), struct EFI_SYSTEM_TABLE *SystemTable)
{
    efi_init(SystemTable);
    ST->ConOut->ClearScreen(ST->ConOut);

    /* 等待按键输入 */
    puts(L"Press any key to shutdown...\r\n");
    getc();

    /* 关机 */
    ST->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, NULL);

    /* 下面的代码正常情况下永远不会被执行 */
    while (TRUE)
        ;
}
