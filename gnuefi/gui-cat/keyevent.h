#ifndef _KEYEVENT_H_
#define _KEYEVENT_H_

#include <efi.h>
#include <efilib.h>

extern EFI_INPUT_KEY ESC_KEY;

void wait_key_pressed(EFI_INPUT_KEY *key);

#endif
