#include <efi.h>
#include <efilib.h>

EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *STIEP;
BOOLEAN pressed = FALSE;

void init()
{
    uefi_call_wrapper(BS->SetWatchdogTimer, 4, 0, 0, 0, NULL);
    uefi_call_wrapper(BS->LocateProtocol, 3, &SimpleTextInputExProtocol, NULL, &STIEP);
}

EFI_STATUS key_notify_handler()
{
    pressed = TRUE;
    return EFI_SUCCESS;
}

EFI_STATUS efi_main(EFI_HANDLE *ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    InitializeLib(ImageHandle, SystemTable);
    init();

    uefi_call_wrapper(ST->ConOut->ClearScreen, 1, ST->ConOut);

    EFI_KEY_DATA key_data = {
        .Key = {
            .ScanCode = 0,
            .UnicodeChar = L'q',
        },
        .KeyState = {
            .KeyShiftState = 0,
            .KeyToggleState = 0,
        },
    };
    void *notify_handle;
    uefi_call_wrapper(STIEP->RegisterKeyNotify, 4, STIEP, &key_data, key_notify_handler, &notify_handle);

    Print(L"Press Q key\n");
    while (!pressed)
        ;

    Print(L"Q key pressed!\n");

    while (TRUE)
        ;

    return EFI_SUCCESS;
}
