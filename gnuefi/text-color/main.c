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

    // set global background color
    uefi_call_wrapper(ST->ConOut->SetAttribute, 2, ST->ConOut, EFI_BACKGROUND_LIGHTGRAY);
    uefi_call_wrapper(ST->ConOut->ClearScreen, 1, ST->ConOut);

    uefi_call_wrapper(ST->ConOut->SetAttribute, 2, ST->ConOut, EFI_LIGHTGREEN | EFI_BACKGROUND_LIGHTGRAY);
    Print(L"Light Green Text\n");

    uefi_call_wrapper(ST->ConOut->SetAttribute, 2, ST->ConOut, EFI_LIGHTRED | EFI_BACKGROUND_LIGHTGRAY);
    Print(L"Light Red Text\n");

    uefi_call_wrapper(ST->ConOut->SetAttribute, 2, ST->ConOut, EFI_LIGHTBLUE | EFI_BACKGROUND_LIGHTGRAY);
    Print(L"Light Blue Text\n");

    uefi_call_wrapper(ST->ConOut->SetAttribute, 2, ST->ConOut, EFI_LIGHTMAGENTA | EFI_BACKGROUND_LIGHTGRAY);
    Print(L"Light Magenta Text\n");

    uefi_call_wrapper(ST->ConOut->SetAttribute, 2, ST->ConOut, EFI_LIGHTCYAN | EFI_BACKGROUND_LIGHTGRAY);
    Print(L"Light Cyan Text\n");

    uefi_call_wrapper(ST->ConOut->SetAttribute, 2, ST->ConOut, EFI_WHITE | EFI_BACKGROUND_LIGHTGRAY);
    Print(L"White Text\n");

    uefi_call_wrapper(ST->ConOut->SetAttribute, 2, ST->ConOut, EFI_MAGENTA | EFI_BACKGROUND_LIGHTGRAY);
    Print(L"Magenta Text\n");

    while (TRUE)
        ;

    return EFI_SUCCESS;
}
