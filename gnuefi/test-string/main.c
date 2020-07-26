#include <efi.h>
#include <efilib.h>

void init()
{
    uefi_call_wrapper(BS->SetWatchdogTimer, 4, 0, 0, 0, NULL);
}

void test_and_print(INT32 id, CHAR16 *string)
{
    EFI_STATUS status = uefi_call_wrapper(ST->ConOut->TestString, 2, ST->ConOut, string);
    Print(L"%u: %s\n", id, (status == EFI_SUCCESS) ? L"Success" : L"Unsupported");
}

EFI_STATUS efi_main(EFI_HANDLE *ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    InitializeLib(ImageHandle, SystemTable);
    init();

    uefi_call_wrapper(ST->ConOut->ClearScreen, 1, ST->ConOut);
    test_and_print(1, L"Hello");
    test_and_print(2, L"你好");
    test_and_print(3, L"Hello, 你好");

    while (TRUE)
        ;

    return EFI_SUCCESS;
}
