#include "efi.h"
#include "common.h"

void timer_callback(void *event __attribute__((unused)), void *context __attribute__((unused)))
{
    puts(L"wait.");
}

void efi_main(void *ImageHandle __attribute__((unused)), struct EFI_SYSTEM_TABLE *SystemTable)
{
    unsigned long long status;
    void *tevent;

    efi_init(SystemTable);
    ST->ConOut->ClearScreen(ST->ConOut);

    /* 创建计时器事件tevent */
    status = ST->BootServices->CreateEvent(EVT_TIMER | EVT_NOTIFY_SIGNAL, TPL_CALLBACK, timer_callback, NULL, &tevent);
    assert(status, L"CreateEvent");

    /* 设置每隔1秒触发tevent事件 */
    status = ST->BootServices->SetTimer(tevent, TimerPeriodic, 10000000);
    assert(status, L"SetTimer");

    while (TRUE)
        ;
}
