#include "efi.h"
#include "common.h"

void efi_main(void *ImageHandle __attribute__((unused)), struct EFI_SYSTEM_TABLE *SystemTable)
{
    int mode;
    unsigned long long status;
    unsigned long long col, row;

    efi_init(SystemTable);
    ST->ConOut->ClearScreen(ST->ConOut);

    for (mode = 0; mode < ST->ConOut->Mode->MaxMode; mode++) {
        status = ST->ConOut->QueryMode(ST->ConOut, mode, &col, &row);
        switch (status) {
        case EFI_SUCCESS:
            puth(mode, 2);
            puts(L": ");
            puth(col, 4);
            puts(L" x ");
            puth(row, 4);
            puts(L"\r\n");
            break;

        case EFI_UNSUPPORTED:
            puth(mode, 2);
            puts(L": unsupported\r\n");
            break;

        default:
            assert(status, L"QueryMode");
            break;
        }
    }

    while (TRUE)
        ;
}
