#include <efi.h>
#include <efilib.h>

void init()
{
    uefi_call_wrapper(BS->SetWatchdogTimer, 4, 0, 0, 0, NULL);
}

EFI_STATUS efi_main(EFI_HANDLE *ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    InitializeLib(ImageHandle, SystemTable);
    init();

    uefi_call_wrapper(ST->ConOut->ClearScreen, 1, ST->ConOut);

    UINTN rows, columns;
    for (INT32 i = 0; i < ST->ConOut->Mode->MaxMode; i++) {
        switch (uefi_call_wrapper(ST->ConOut->QueryMode, 4, ST->ConOut, i, &columns, &rows)) {
            case EFI_SUCCESS:
                Print(L"%d: %u x %u\n", i, columns, rows);
                break;
            case EFI_UNSUPPORTED:
                Print(L"%d: Unsupported\n", i);
                break;
            default:
                return EFI_DEVICE_ERROR;
        }
    }

    while (TRUE)
        ;

    return EFI_SUCCESS;
}
