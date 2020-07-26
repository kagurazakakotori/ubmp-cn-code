#include "efi.h"
#include "common.h"

unsigned char is_exit = FALSE;

unsigned long long key_notice(struct EFI_KEY_DATA *KeyData __attribute__((unused)))
{
    is_exit = TRUE;

    return EFI_SUCCESS;
}

void efi_main(void *ImageHandle __attribute__((unused)), struct EFI_SYSTEM_TABLE *SystemTable)
{
    unsigned long long status;
    struct EFI_KEY_DATA key_data = {{0, L'q'}, {0, 0}};
    void *notify_handle;

    efi_init(SystemTable);
    ST->ConOut->ClearScreen(ST->ConOut);

    puts(L"Waiting for the 'q' key input...\r\n");

    status = STIEP->RegisterKeyNotify(STIEP, &key_data, key_notice, &notify_handle);
    assert(status, L"RegisterKeyNotify");

    while (!is_exit)
        ;

    puts(L"exit.\r\n");

    while (TRUE)
        ;
}
