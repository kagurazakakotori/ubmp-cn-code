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
    while (TRUE) {
        for (INT32 i = 0; i < ST->ConOut->Mode->MaxMode; i++) {
            if (uefi_call_wrapper(ST->ConOut->QueryMode, 4, ST->ConOut, i, &columns, &rows) != EFI_SUCCESS) {
                continue;
            }

            uefi_call_wrapper(ST->ConOut->SetMode, 2, ST->ConOut, i);
            uefi_call_wrapper(ST->ConOut->ClearScreen, 1, ST->ConOut);
            Print(L"Current text mode: %d : %u x %u\n", i, columns, rows);
            Print(L"Press any key to continue...\n");

            Pause();
        }
    }

    return EFI_SUCCESS;
}
