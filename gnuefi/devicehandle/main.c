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
    EFI_DEVICE_PATH_PROTOCOL *device_path;
    CHAR16 *devicehandle;

    uefi_call_wrapper(BS->OpenProtocol, 6, image, &LoadedImageProtocol, &loaded_image, image, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    uefi_call_wrapper(BS->OpenProtocol, 6, loaded_image->DeviceHandle, &DevicePathProtocol, &device_path, image, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    devicehandle = (CHAR16 *)uefi_call_wrapper(DPTTP->ConvertDevicePathToText, 3, device_path, FALSE, FALSE);
    Print(L"Device handle: %s\n", devicehandle);

    while (TRUE)
        ;

    return EFI_SUCCESS;
}
