#include <efi.h>
#include <efilib.h>

EFI_DEVICE_PATH_TO_TEXT_PROTOCOL *DPTTP;
EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL *DPFTP;
EFI_DEVICE_PATH_UTILITIES_PROTOCOL *DPUP;

void init()
{
    uefi_call_wrapper(BS->SetWatchdogTimer, 4, 0, 0, 0, NULL);
    uefi_call_wrapper(BS->LocateProtocol, 3, &DevicePathToTextProtocol, NULL, &DPTTP);
    uefi_call_wrapper(BS->LocateProtocol, 3, &DevicePathFromTextProtocol, NULL, &DPFTP);
    uefi_call_wrapper(BS->LocateProtocol, 3, &DevicePathUtilitiesProtocol, NULL, &DPUP);
}

EFI_STATUS efi_main(EFI_HANDLE image, EFI_SYSTEM_TABLE *systab)
{
    InitializeLib(image, systab);
    init();

    uefi_call_wrapper(ST->ConOut->ClearScreen, 1, ST->ConOut);

    EFI_LOADED_IMAGE_PROTOCOL *loaded_image;
    EFI_DEVICE_PATH_PROTOCOL *device_path, *image_path, *device_path_merged;
    EFI_STATUS status;
    EFI_HANDLE child_image;
    CHAR16 *pathstr;
    CHAR16 statusstr[32];

    uefi_call_wrapper(BS->OpenProtocol, 6, image, &LoadedImageProtocol, &loaded_image, image, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    uefi_call_wrapper(BS->OpenProtocol, 6, loaded_image->DeviceHandle, &DevicePathProtocol, &device_path, image, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    image_path = (EFI_DEVICE_PATH_PROTOCOL *)uefi_call_wrapper(DPFTP->ConvertTextToDevicePath, 1, L"\\test.efi");
    device_path_merged = (EFI_DEVICE_PATH_PROTOCOL *)uefi_call_wrapper(DPUP->AppendDevicePath, 2, device_path, image_path);
    pathstr = (CHAR16 *)uefi_call_wrapper(DPTTP->ConvertDevicePathToText, 3, device_path_merged, FALSE, FALSE);
    Print(L"Merged device path: %s\n", pathstr);

    status = uefi_call_wrapper(BS->LoadImage, 6, FALSE, image, device_path_merged, NULL, 0, &child_image);
    StatusToString(statusstr, status);
    Print(L"LoadImage status: %s\n", statusstr);

    while (TRUE)
        ;

    return EFI_SUCCESS;
}
