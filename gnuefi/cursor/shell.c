#include "shell.h"

void shell()
{
    CHAR16 command[MAX_COMMAND_LEN];

    while (TRUE) {
        Input(L"poiOS> ", command, MAX_COMMAND_LEN);
        Print(L"\r\n");

        if (StrLen(command) == 0) {
            continue;
        }

        if (!StrCmp(L"hello", command)) {
            Print(L"Hello UEFI!\r\n");
        } else if (!StrCmp(L"rect", command)) {
            rect();
        } else if (!StrCmp(L"gui", command)) {
            gui();
        } else if (!StrCmp(L"pstat", command)) {
            pstat();
        } else {
            Print(L"Command not found.\r\n");
        }
    }
}

void rect()
{
    struct Rect rect = {10, 10, 100, 200};
    draw_rect(rect, white);
}

void pstat()
{
    EFI_SIMPLE_POINTER_STATE state;

    uefi_call_wrapper(SPP->Reset, 2, SPP, FALSE);

    while (TRUE) {
        WaitForSingleEvent(SPP->WaitForInput, 0);

        if (!uefi_call_wrapper(SPP->GetState, 2, SPP, &state)) {
            Print(L"X: %.10d, Y: %.10d, Z: %d, Left: %d, Right: %d\r\n", state.RelativeMovementX, state.RelativeMovementY, state.RelativeMovementZ, state.LeftButton, state.RightButton);
        }
    }
}
