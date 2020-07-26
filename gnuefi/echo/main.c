#include <efi.h>
#include <efilib.h>

void init()
{
    uefi_call_wrapper(BS->SetWatchdogTimer, 4, 0, 0, 0, NULL);
}

EFI_STATUS efi_main(EFI_HANDLE image, EFI_SYSTEM_TABLE *systab)
{
    InitializeLib(image, systab);
    init();

    uefi_call_wrapper(ST->ConOut->ClearScreen, 1, ST->ConOut);

    EFI_INPUT_KEY key;
    CHAR16 buf[2];
    CHAR16 *str;

    while (TRUE) {
        if (!uefi_call_wrapper(ST->ConIn->ReadKeyStroke, 2, ST->ConIn, &key)) {
            if (key.UnicodeChar == L'\r' || key.UnicodeChar == L'\n') {
                str = L"\r\n";
            } else if (key.UnicodeChar == L'\b') {
                str = L"\b \b";
            } else {
                buf[0] = key.UnicodeChar;
                buf[1] = L'\0';
                str = buf;
            }

            Print(L"%s", str);
        }
    }

    return EFI_SUCCESS;
}
