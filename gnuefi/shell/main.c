#include <efi.h>
#include <efilib.h>
#include "shell.h"

EFI_STATUS efi_main(EFI_HANDLE *ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    InitializeLib(ImageHandle, SystemTable);

    uefi_call_wrapper(ST->ConOut->ClearScreen, 1, ST->ConOut);
    shell();

    return EFI_SUCCESS;
}
