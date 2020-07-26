#ifndef _EFI_H_
#define _EFI_H_

struct EFI_INPUT_KEY {
    unsigned short ScanCode;
    unsigned short UnicodeChar;
};

struct EFI_SYSTEM_TABLE {
    char _buf1[44];
    struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
        unsigned long long _buf;
        unsigned long long (*ReadKeyStroke)(
            struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
            struct EFI_INPUT_KEY *Key);
        void *WaitForKey;
    } * ConIn;
    unsigned long long _buf2;
    struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
        unsigned long long _buf;
        unsigned long long (*OutputString)(
            struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
            unsigned short *String);
        unsigned long long _buf2[4];
        unsigned long long (*ClearScreen)(
            struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);
    } * ConOut;
    unsigned long long _buf3[3];
    struct EFI_BOOT_SERVICES {
        char _buf1[24];

        // Task Priority Services
        unsigned long long _buf2[2];

        // Memory Services
        unsigned long long _buf3[5];

        // Event & Timer Services
        unsigned long long _buf4[2];
        unsigned long long (*WaitForEvent)(
            unsigned long long NumberOfEvents,
            void **Event,
            unsigned long long *Index);
        unsigned long long _buf4_2[3];

        // Protocol Handler Services
        unsigned long long _buf5[9];

        // Image Services
        unsigned long long _buf6[5];

        // Miscellaneous Services
        unsigned long long _buf7[2];
        unsigned long long (*SetWatchdogTimer)(
            unsigned long long Timeout,
            unsigned long long WatchdogCode,
            unsigned long long DataSize,
            unsigned short *WatchdogData);

        // DriverSupport Services
        unsigned long long _buf8[2];

        // Open and Close Protocol Services
        unsigned long long _buf9[3];

        // Library Services
        unsigned long long _buf10[5];

        // 32-bit CRC Services
        unsigned long long _buf11;

        // Miscellaneous Services
        unsigned long long _buf12[3];
    } * BootServices;
};

extern struct EFI_SYSTEM_TABLE *ST;

void efi_init(struct EFI_SYSTEM_TABLE *SystemTable);

#endif
