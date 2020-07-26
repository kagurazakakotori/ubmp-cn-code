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
        } else if (!StrCmp(L"ls", command)) {
            ls();
        } else if (!StrCmp(L"cat", command)) {
            cat(L"abc");
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

void ls()
{
    EFI_FILE_PROTOCOL *root;
    UINT8 buffer[FILE_BUFFER_SIZE];
    UINTN buffer_size;
    EFI_FILE_INFO *fileinfo;

    uefi_call_wrapper(SFSP->OpenVolume, 2, SFSP, &root);

    int i = 0;
    while (TRUE) {
        buffer_size = sizeof(buffer);
        uefi_call_wrapper(root->Read, 3, root, &buffer_size, buffer);

        if (buffer_size == 0) { // break when there are no more entries
            break;
        }

        fileinfo = (EFI_FILE_INFO *)buffer;
        ZeroMem(filelist.files[i].name, MAX_FILENAME_LEN);
        StrnCpy(filelist.files[i].name, fileinfo->FileName, MAX_FILENAME_LEN - 1);
        Print(L"%s ", filelist.files[i].name);
        i++;
    }
    Print(L"\r\n");

    filelist.file_count = i;
    uefi_call_wrapper(root->Close, 1, root);
}

void cat(CHAR16 *filename)
{
    EFI_FILE_PROTOCOL *root, *file;
    UINT8 buffer[FILE_BUFFER_SIZE];
    UINTN buffer_size = sizeof(buffer);

    ZeroMem(buffer, sizeof(buffer));

    uefi_call_wrapper(SFSP->OpenVolume, 2, SFSP, &root);
    uefi_call_wrapper(root->Open, 5, root, &file, filename, EFI_FILE_MODE_READ, 0);
    uefi_call_wrapper(file->Read, 3, file, &buffer_size, buffer);

    Print(L"%s", (CHAR16 *)buffer);

    uefi_call_wrapper(file->Close, 1, file);
    uefi_call_wrapper(root->Close, 1, root);
}
