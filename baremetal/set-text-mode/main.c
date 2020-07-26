#include "efi.h"
#include "common.h"

void efi_main(void *ImageHandle __attribute__((unused)), struct EFI_SYSTEM_TABLE *SystemTable)
{
    int mode;
    unsigned long long status;
    unsigned long long col, row;

    efi_init(SystemTable);
    ST->ConOut->ClearScreen(ST->ConOut);

    while (TRUE) {
        for (mode = 0; mode < ST->ConOut->Mode->MaxMode; mode++) {
            status = ST->ConOut->QueryMode(ST->ConOut, mode, &col, &row);
            if (status)
                continue;

            ST->ConOut->SetMode(ST->ConOut, mode);
            ST->ConOut->ClearScreen(SystemTable->ConOut);

            puts(L"mode=");
            puth(mode, 1);
            puts(L", col=0x");
            puth(col, 2);
            puts(L", row=0x");
            puth(row, 2);
            puts(L"\r\n");
            puts(L"\r\n");
            puts(L"Hello UEFI!");

            getc();
        }
    }
}
