#include "efi.h"
#include "common.h"
#include "graphics.h"

#define IMG_WIDTH  256
#define IMG_HEIGHT 256

void efi_main(void *ImageHandle __attribute__((unused)), struct EFI_SYSTEM_TABLE *SystemTable)
{
    unsigned long long status;
    struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *img_buf, *t;
    unsigned int i, j;

    efi_init(SystemTable);
    ST->ConOut->ClearScreen(ST->ConOut);

    /* 分配图像所需要的内存空间 */
    status = ST->BootServices->AllocatePool(
        EfiLoaderData,
        IMG_WIDTH * IMG_HEIGHT * sizeof(struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL),
        (void **)&img_buf);
    assert(status, L"AllocatePool");

    /* 生成图像 */
    t = img_buf;
    for (i = 0; i < IMG_HEIGHT; i++) {
        for (j = 0; j < IMG_WIDTH; j++) {
            t->Blue = i;
            t->Green = j;
            t->Red = 0;
            t->Reserved = 255;
            t++;
        }
    }

    /* 绘制图像(写入帧缓冲区) */
    blt((unsigned char *)img_buf, IMG_WIDTH, IMG_HEIGHT);

    /* 释放先前分配的内存 */
    status = ST->BootServices->FreePool((void *)img_buf);
    assert(status, L"FreePool");

    while (TRUE)
        ;
}
