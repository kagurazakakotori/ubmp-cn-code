#include <efi.h>
#include <efilib.h>

EFI_DEVICE_PATH_TO_TEXT_PROTOCOL *DPTTP;

void init()
{
    uefi_call_wrapper(BS->SetWatchdogTimer, 4, 0, 0, 0, NULL);
    uefi_call_wrapper(BS->LocateProtocol, 3, &DevicePathToTextProtocol, NULL, &DPTTP);
}

EFI_STATUS efi_main(EFI_HANDLE image, EFI_SYSTEM_TABLE *systab)
{
    InitializeLib(image, systab);
    init();

    uefi_call_wrapper(ST->ConOut->ClearScreen, 1, ST->ConOut);

    EFI_LOADED_IMAGE_PROTOCOL *loaded_image;
    EFI_DEVICE_PATH_PROTOCOL *path;
    EFI_STATUS status;
    EFI_HANDLE child_image;
    CHAR16 *pathstr;
    CHAR16 statusstr[32];

    uefi_call_wrapper(BS->OpenProtocol, 6, image, &LoadedImageProtocol, &loaded_image, image, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    path = FileDevicePath(loaded_image->DeviceHandle, L"\\test.efi");
    pathstr = (CHAR16 *)uefi_call_wrapper(DPTTP->ConvertDevicePathToText, 3, path, FALSE, FALSE);
    Print(L"Image device path: %s\n", pathstr);

    status = uefi_call_wrapper(BS->LoadImage, 6, FALSE, image, path, NULL, 0, &child_image);
    StatusToString(statusstr, status);
    Print(L"LoadImage status: %s\n", statusstr);

    uefi_call_wrapper(BS->StartImage, 3, child_image, NULL, NULL);

    while (TRUE)
        ;

    return EFI_SUCCESS;
}
