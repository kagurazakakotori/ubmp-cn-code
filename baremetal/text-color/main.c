#include "efi.h"
#include "common.h"

void efi_main(void *ImageHandle __attribute__((unused)), struct EFI_SYSTEM_TABLE *SystemTable)
{
    efi_init(SystemTable);

    puts(L" ");

    ST->ConOut->SetAttribute(ST->ConOut, EFI_LIGHTGREEN | EFI_BACKGROUND_LIGHTGRAY);
    ST->ConOut->ClearScreen(ST->ConOut);
    puts(L"Light Green Text\r\n");

    ST->ConOut->SetAttribute(ST->ConOut, EFI_LIGHTRED | EFI_BACKGROUND_LIGHTGRAY);
    puts(L"Light Red Text\r\n");

    ST->ConOut->SetAttribute(ST->ConOut, EFI_LIGHTBLUE | EFI_BACKGROUND_LIGHTGRAY);
    puts(L"Light Blue Text\r\n");

    ST->ConOut->SetAttribute(ST->ConOut, EFI_LIGHTMAGENTA | EFI_BACKGROUND_LIGHTGRAY);
    puts(L"Light Magenta Text\r\n");

    ST->ConOut->SetAttribute(ST->ConOut, EFI_WHITE | EFI_BACKGROUND_LIGHTGRAY);
    puts(L"White Text\r\n");

    ST->ConOut->SetAttribute(ST->ConOut, EFI_LIGHTCYAN | EFI_BACKGROUND_LIGHTGRAY);
    puts(L"Light Cyan Text\r\n");

    ST->ConOut->SetAttribute(ST->ConOut, EFI_MAGENTA | EFI_BACKGROUND_LIGHTGRAY);
    puts(L"Magenta Text\r\n");

    while (TRUE)
        ;
}
