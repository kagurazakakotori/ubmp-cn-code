#include "efi.h"
#include "common.h"

void efi_main(void *ImageHandle, struct EFI_SYSTEM_TABLE *SystemTable)
{
    struct EFI_LOADED_IMAGE_PROTOCOL *lip;
    struct EFI_DEVICE_PATH_PROTOCOL *dev_path;
    struct EFI_DEVICE_PATH_PROTOCOL *dev_node;
    struct EFI_DEVICE_PATH_PROTOCOL *dev_path_merged;
    unsigned long long status;
    void *image;

    efi_init(SystemTable);
    ST->ConOut->ClearScreen(ST->ConOut);

    /* 获取ImageHandle的EFI_LOADED_IMAGE_PROTOCOL(lip) */
    status = ST->BootServices->OpenProtocol(ImageHandle, &lip_guid, (void **)&lip, ImageHandle, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    assert(status, L"OpenProtocol(lip)");

    /* 获取lip->DeviceHandle的EFI_DEVICE_PATH_PROTOCOL(dev_path) */
    status = ST->BootServices->OpenProtocol(
        lip->DeviceHandle, &dpp_guid, (void **)&dev_path, ImageHandle,
        NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    assert(status, L"OpenProtocol(dpp)");

    /* 创建bzImage.efi的设备节点 */
    dev_node = DPFTP->ConvertTextToDeviceNode(L"bzImage.efi");

    /* 把dev_node附加到dev_path后 */
    dev_path_merged = DPUP->AppendDeviceNode(dev_path, dev_node);

    /* 把dev_node附加到dev_path后 */
    puts(L"dev_path_merged: ");
    puts(DPTTP->ConvertDevicePathToText(dev_path_merged, FALSE, FALSE));
    puts(L"\r\n");

    /* 把dev_path_merged转换成字符串并显示 */
    status = ST->BootServices->LoadImage(FALSE, ImageHandle, dev_path_merged, NULL, 0, &image);
    assert(status, L"LoadImage");
    puts(L"LoadImage: Success!\r\n");

    /* 运行image */
    status = ST->BootServices->StartImage(image, NULL, NULL);
    assert(status, L"StartImage");
    puts(L"StartImage: Success!\r\n");

    while (TRUE)
        ;
}
