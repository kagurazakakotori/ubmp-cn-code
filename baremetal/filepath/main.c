#include "efi.h"
#include "common.h"

void efi_main(void *ImageHandle, struct EFI_SYSTEM_TABLE *SystemTable)
{
    unsigned long long status;
    struct EFI_LOADED_IMAGE_PROTOCOL *lip;

    efi_init(SystemTable);
    ST->ConOut->ClearScreen(ST->ConOut);

    status = ST->BootServices->OpenProtocol(ImageHandle, &lip_guid, (void **)&lip, ImageHandle, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    assert(status, L"OpenProtocol");

    puts(L"lip->FilePath: ");
    puts(DPTTP->ConvertDevicePathToText(lip->FilePath, FALSE, FALSE));
    puts(L"\r\n");

    while (TRUE)
        ;
}
