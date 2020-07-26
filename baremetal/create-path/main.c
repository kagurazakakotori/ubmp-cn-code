#include "efi.h"
#include "common.h"

void efi_main(void *ImageHandle __attribute__((unused)), struct EFI_SYSTEM_TABLE *SystemTable)
{
    struct EFI_DEVICE_PATH_PROTOCOL *dev_path;

    efi_init(SystemTable);
    ST->ConOut->ClearScreen(ST->ConOut);

    dev_path = DPFTP->ConvertTextToDevicePath(L"\\test.efi");
    puts(L"dev_path: ");
    puts(DPTTP->ConvertDevicePathToText(dev_path, FALSE, FALSE));
    puts(L"\r\n");

    while (TRUE)
        ;
}
