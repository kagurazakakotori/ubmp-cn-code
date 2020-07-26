#include "efi.h"
#include "common.h"

struct EFI_SYSTEM_TABLE *ST;
struct EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;

void efi_init(struct EFI_SYSTEM_TABLE *SystemTable)
{
    struct EFI_GUID gop_guid = {0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}};

    ST = SystemTable;
    ST->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
    ST->BootServices->LocateProtocol(&gop_guid, NULL, (void **)&GOP);
}
