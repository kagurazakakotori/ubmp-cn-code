#include "efi.h"
#include "common.h"

void efi_main(void *ImageHandle __attribute__((unused)), struct EFI_SYSTEM_TABLE *SystemTable)
{
    unsigned long long status;
    void *tevent;
    void *wait_list[1];
    unsigned long long idx;

    efi_init(SystemTable);
    ST->ConOut->ClearScreen(ST->ConOut);

    /* 创建计时器事件tevent */
    status = ST->BootServices->CreateEvent(EVT_TIMER, 0, NULL, NULL, &tevent);
    assert(status, L"CreateEvent");

    /* 为WaitForEvent()创建要等待的事件数组 */
    wait_list[0] = tevent;

    while (TRUE) {
        /* 设置1秒后触发tevent事件 */
        status = ST->BootServices->SetTimer(tevent, TimerRelative, 10000000);
        assert(status, L"SetTimer");

        /* 等待tevent发生 */
        status = ST->BootServices->WaitForEvent(1, wait_list, &idx);
        assert(status, L"WaitForEvent");

        /* 在屏幕上输出"wait." */
        puts(L"wait.");
    }
}
