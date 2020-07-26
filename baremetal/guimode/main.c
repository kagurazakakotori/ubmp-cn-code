#include "efi.h"
#include "shell.h"

void efi_main(void *ImageHandle __attribute__((unused)), struct EFI_SYSTEM_TABLE *SystemTable)
{
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    efi_init(SystemTable);

    shell();
}
