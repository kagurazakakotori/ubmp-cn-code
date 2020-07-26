#ifndef _EFI_H_
#define _EFI_H_

#define EFI_FILE_MODE_READ   0x0000000000000001
#define EFI_FILE_MODE_WRITE  0x0000000000000002
#define EFI_FILE_MODE_CREATE 0x8000000000000000

#define EFI_FILE_READ_ONLY 0x0000000000000001

//*******************************************************
// Attributes
//*******************************************************
#define EFI_BLACK        0x00
#define EFI_BLUE         0x01
#define EFI_GREEN        0x02
#define EFI_CYAN         0x03
#define EFI_RED          0x04
#define EFI_MAGENTA      0x05
#define EFI_BROWN        0x06
#define EFI_LIGHTGRAY    0x07
#define EFI_BRIGHT       0x08
#define EFI_DARKGRAY     0x08
#define EFI_LIGHTBLUE    0x09
#define EFI_LIGHTGREEN   0x0A
#define EFI_LIGHTCYAN    0x0B
#define EFI_LIGHTRED     0x0C
#define EFI_LIGHTMAGENTA 0x0D
#define EFI_YELLOW       0x0E
#define EFI_WHITE        0x0F

#define EFI_BACKGROUND_BLACK     0x00
#define EFI_BACKGROUND_BLUE      0x10
#define EFI_BACKGROUND_GREEN     0x20
#define EFI_BACKGROUND_CYAN      0x30
#define EFI_BACKGROUND_RED       0x40
#define EFI_BACKGROUND_MAGENTA   0x50
#define EFI_BACKGROUND_BROWN     0x60
#define EFI_BACKGROUND_LIGHTGRAY 0x70

#define EFI_SUCCESS     0
#define EFI_ERROR       0x8000000000000000
#define EFI_UNSUPPORTED (EFI_ERROR | 3)

#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL  0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL        0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL       0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER 0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER           0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE           0x00000020

struct EFI_INPUT_KEY {
    unsigned short ScanCode;
    unsigned short UnicodeChar;
};

struct EFI_GUID {
    unsigned int Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char Data4[8];
};

enum EFI_MEMORY_TYPE {
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiMaxMemoryType
};

struct EFI_DEVICE_PATH_PROTOCOL {
    unsigned char Type;
    unsigned char SubType;
    unsigned char Length[2];
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
        unsigned long long (*TestString)(
            struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
            unsigned short *String);
        unsigned long long (*QueryMode)(
            struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
            unsigned long long ModeNumber,
            unsigned long long *Columns,
            unsigned long long *Rows);
        unsigned long long (*SetMode)(
            struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
            unsigned long long ModeNumber);
        unsigned long long (*SetAttribute)(
            struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
            unsigned long long Attribute);
        unsigned long long (*ClearScreen)(
            struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);
        unsigned long long _buf4[2];
        struct SIMPLE_TEXT_OUTPUT_MODE {
            int MaxMode;
            int Mode;
            int Attribute;
            int CursorColumn;
            int CursorRow;
            unsigned char CursorVisible;
        } * Mode;
    } * ConOut;
    unsigned long long _buf3[3];
    struct EFI_BOOT_SERVICES {
        char _buf1[24];

        //
        // Task Priority Services
        //
        unsigned long long _buf2[2];

        //
        // Memory Services
        //
        unsigned long long _buf3[5];

        //
        // Event & Timer Services
        //
        unsigned long long _buf4[2];
        unsigned long long (*WaitForEvent)(
            unsigned long long NumberOfEvents,
            void **Event,
            unsigned long long *Index);
        unsigned long long _buf4_2[3];

        //
        // Protocol Handler Services
        //
        unsigned long long _buf5[9];

        //
        // Image Services
        //
        unsigned long long _buf6[5];

        //
        // Miscellaneous Services
        //
        unsigned long long _buf7[2];
        unsigned long long (*SetWatchdogTimer)(
            unsigned long long Timeout,
            unsigned long long WatchdogCode,
            unsigned long long DataSize,
            unsigned short *WatchdogData);

        //
        // DriverSupport Services
        //
        unsigned long long _buf8[2];

        //
        // Open and Close Protocol Services
        //
        unsigned long long (*OpenProtocol)(
            void *Handle,
            struct EFI_GUID *Protocol,
            void **Interface,
            void *AgentHandle,
            void *ControllerHandle,
            unsigned int Attributes);
        unsigned long long _buf9[2];

        //
        // Library Services
        //
        unsigned long long _buf10[2];
        unsigned long long (*LocateProtocol)(
            struct EFI_GUID *Protocol,
            void *Registration,
            void **Interface);
        unsigned long long _buf10_2[2];

        //
        // 32-bit CRC Services
        //
        unsigned long long _buf11;

        //
        // Miscellaneous Services
        //
        unsigned long long _buf12[3];
    } * BootServices;
};

struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL {
    unsigned char Blue;
    unsigned char Green;
    unsigned char Red;
    unsigned char Reserved;
};

struct EFI_GRAPHICS_OUTPUT_PROTOCOL {
    unsigned long long _buf[3];
    struct EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE {
        unsigned int MaxMode;
        unsigned int Mode;
        struct EFI_GRAPHICS_OUTPUT_MODE_INFORMATION {
            unsigned int Version;
            unsigned int HorizontalResolution;
            unsigned int VerticalResolution;
            enum EFI_GRAPHICS_PIXEL_FORMAT {
                PixelRedGreenBlueReserved8BitPerColor,
                PixelBlueGreenRedReserved8BitPerColor,
                PixelBitMask,
                PixelBltOnly,
                PixelFormatMax
            } PixelFormat;
        } * Info;
        unsigned long long SizeOfInfo;
        unsigned long long FrameBufferBase;
    } * Mode;
};

struct EFI_SIMPLE_POINTER_STATE {
    int RelativeMovementX;
    int RelativeMovementY;
    int RelativeMovementZ;
    unsigned char LeftButton;
    unsigned char RightButton;
};

struct EFI_SIMPLE_POINTER_PROTOCOL {
    unsigned long long (*Reset)(
        struct EFI_SIMPLE_POINTER_PROTOCOL *This,
        unsigned char ExtendedVerification);
    unsigned long long (*GetState)(
        struct EFI_SIMPLE_POINTER_PROTOCOL *This,
        struct EFI_SIMPLE_POINTER_STATE *State);
    void *WaitForInput;
};

struct EFI_FILE_INFO {
    unsigned char _buf[80];
    unsigned short FileName[];
};

struct EFI_FILE_PROTOCOL {
    unsigned long long _buf;
    unsigned long long (*Open)(struct EFI_FILE_PROTOCOL *This,
                               struct EFI_FILE_PROTOCOL **NewHandle,
                               unsigned short *FileName,
                               unsigned long long OpenMode,
                               unsigned long long Attributes);
    unsigned long long (*Close)(struct EFI_FILE_PROTOCOL *This);
    unsigned long long _buf2;
    unsigned long long (*Read)(struct EFI_FILE_PROTOCOL *This,
                               unsigned long long *BufferSize,
                               void *Buffer);
    unsigned long long (*Write)(struct EFI_FILE_PROTOCOL *This,
                                unsigned long long *BufferSize,
                                void *Buffer);
    unsigned long long _buf3[4];
    unsigned long long (*Flush)(struct EFI_FILE_PROTOCOL *This);
};

struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL {
    unsigned long long Revision;
    unsigned long long (*OpenVolume)(
        struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This,
        struct EFI_FILE_PROTOCOL **Root);
};

struct EFI_KEY_STATE {
    unsigned int KeyShiftState;
    unsigned char KeyToggleState;
};

struct EFI_KEY_DATA {
    struct EFI_INPUT_KEY Key;
    struct EFI_KEY_STATE KeyState;
};

struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL {
    unsigned long long (*Reset)(
        struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
        unsigned char ExtendedVerification);
    unsigned long long (*ReadKeyStrokeEx)(
        struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
        struct EFI_KEY_DATA *KeyData);
    void *WaitForKeyEx;
    unsigned long long (*SetState)(
        struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
        unsigned char *KeyToggleState);
    unsigned long long (*RegisterKeyNotify)(
        struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
        struct EFI_KEY_DATA *KeyData,
        unsigned long long (*KeyNotificationFunction)(
            struct EFI_KEY_DATA *KeyData),
        void **NotifyHandle);
    unsigned long long (*UnregisterKeyNotify)(
        struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
        void *NotificationHandle);
};

struct EFI_LOADED_IMAGE_PROTOCOL {
    unsigned int Revision;
    void *ParentHandle;
    struct EFI_SYSTEM_TABLE *SystemTable;
    // Source location of the image
    void *DeviceHandle;
    struct EFI_DEVICE_PATH_PROTOCOL *FilePath;
    void *Reserved;
    // Image’s load options
    unsigned int LoadOptionsSize;
    void *LoadOptions;
    // Location where image was loaded
    void *ImageBase;
    unsigned long long ImageSize;
    enum EFI_MEMORY_TYPE ImageCodeType;
    enum EFI_MEMORY_TYPE ImageDataType;
    unsigned long long (*Unload)(void *ImageHandle);
};

struct EFI_DEVICE_PATH_TO_TEXT_PROTOCOL {
    unsigned long long _buf;
    unsigned short *(*ConvertDevicePathToText)(
        const struct EFI_DEVICE_PATH_PROTOCOL *DeviceNode,
        unsigned char DisplayOnly,
        unsigned char AllowShortcuts);
};

extern struct EFI_SYSTEM_TABLE *ST;
extern struct EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
extern struct EFI_SIMPLE_POINTER_PROTOCOL *SPP;
extern struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SFSP;
extern struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *STIEP;
extern struct EFI_DEVICE_PATH_TO_TEXT_PROTOCOL *DPTTP;
extern struct EFI_GUID lip_guid;

void efi_init(struct EFI_SYSTEM_TABLE *SystemTable);

#endif
