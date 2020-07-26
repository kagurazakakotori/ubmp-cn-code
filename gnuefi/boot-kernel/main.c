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

    EFI_LOADED_IMAGE_PROTOCOL *loaded_image;
    EFI_DEVICE_PATH_PROTOCOL *path;
    EFI_HANDLE kernel_image;

    uefi_call_wrapper(BS->OpenProtocol, 6, image, &LoadedImageProtocol, &loaded_image, image, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    path = FileDevicePath(loaded_image->DeviceHandle, L"\\bzImage");
    uefi_call_wrapper(BS->LoadImage, 6, FALSE, image, path, NULL, 0, &kernel_image);
    uefi_call_wrapper(BS->StartImage, 3, kernel_image, NULL, NULL);

    while (TRUE)
        ;

    return EFI_SUCCESS;
}
