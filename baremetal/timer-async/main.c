#include "efi.h"
#include "common.h"

void tick_callback(void *event __attribute__((unused)), void *context __attribute__((unused)))
{
    puts(L"tick.");
}

void efi_main(void *ImageHandle __attribute__((unused)), struct EFI_SYSTEM_TABLE *SystemTable)
{
    unsigned long long status;
    void *tickevent, *tockevent;
    void *wait_list[1];
    unsigned long long idx;

    efi_init(SystemTable);
    ST->ConOut->ClearScreen(ST->ConOut);

    /* 创建计时器事件tickevent, tockevent */
    status = ST->BootServices->CreateEvent(EVT_TIMER | EVT_NOTIFY_SIGNAL, TPL_CALLBACK, tick_callback, NULL, &tickevent);
    assert(status, L"CreateEvent");
    status = ST->BootServices->CreateEvent(EVT_TIMER, 0, NULL, NULL, &tockevent);
    assert(status, L"CreateEvent");

    /* 设置每隔1秒触发tickevent事件 */
    status = ST->BootServices->SetTimer(tickevent, TimerPeriodic, 10000000);
    assert(status, L"SetTimer");

    /* 为WaitForEvent()创建要等待的事件数组 */
    wait_list[0] = tockevent;

    while (TRUE) {
        /* 设置2秒后触发tevent事件 */
        status = ST->BootServices->SetTimer(tockevent, TimerRelative, 20000000);
        assert(status, L"SetTimer");

        /* 等待tevent发生 */
        status = ST->BootServices->WaitForEvent(1, wait_list, &idx);
        assert(status, L"WaitForEvent");

        /* 在屏幕上输出"tock." */
        puts(L"tock.");
    }
}
