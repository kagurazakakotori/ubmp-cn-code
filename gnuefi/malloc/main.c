#include <efi.h>
#include <efilib.h>

#define IMG_WIDTH  256
#define IMG_HEIGHT 256

EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;

void init()
{
    uefi_call_wrapper(BS->SetWatchdogTimer, 4, 0, 0, 0, NULL);
    uefi_call_wrapper(BS->LocateProtocol, 3, &GraphicsOutputProtocol, NULL, &GOP);
}

EFI_STATUS efi_main(EFI_HANDLE *ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    InitializeLib(ImageHandle, SystemTable);
    init();

    uefi_call_wrapper(ST->ConOut->ClearScreen, 1, ST->ConOut);

    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *image_buffer;
    EFI_STATUS status;

    /* 分配图像所需要的内存空间 */
    status = uefi_call_wrapper(ST->BootServices->AllocatePool, 3, EfiLoaderData, IMG_WIDTH * IMG_HEIGHT * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL), &image_buffer);
    if (EFI_ERROR(status)) {
        Print(L"Failed to allocate memory\n");
        Pause();
    }

    /* 生成图像 */
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *ppixel = image_buffer;
    for (int i = 0; i < IMG_HEIGHT; i++) {
        for (int j = 0; j < IMG_WIDTH; j++) {
            ppixel->Blue = i;
            ppixel->Green = j;
            ppixel->Red = 0;
            ppixel->Reserved = 255;
            ppixel++;
        }
    }

    /* 绘制图像(写入帧缓冲区) */
    uefi_call_wrapper(GOP->Blt, 10, GOP, image_buffer, EfiBltBufferToVideo, 0, 0, 0, 0, IMG_WIDTH, IMG_HEIGHT, IMG_WIDTH * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));

    /* 释放先前分配的内存 */
    status = uefi_call_wrapper(ST->BootServices->FreePool, 1, image_buffer);
    if (EFI_ERROR(status)) {
        Print(L"Failed to free memory\n");
        Pause();
    }

    while (TRUE)
        ;

    return EFI_SUCCESS;
}
