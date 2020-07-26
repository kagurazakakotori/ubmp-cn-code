#include "keyevent.h"

EFI_INPUT_KEY ESC_KEY = {
    .ScanCode = SCAN_ESC,
    .UnicodeChar = 0,
};

void wait_key_pressed(EFI_INPUT_KEY *key)
{
    EFI_INPUT_KEY key_pressed;
    WaitForSingleEvent(ST->ConIn->WaitForKey, 0);
    while (uefi_call_wrapper(ST->ConIn->ReadKeyStroke, 2, ST->ConIn, &key_pressed)) {
        if (!CompareMem(key, &key_pressed, sizeof(EFI_INPUT_KEY))) {
            return;
        }
    }
}