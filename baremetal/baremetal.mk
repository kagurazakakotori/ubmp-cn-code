ARCH    = x86_64

CC      = x86_64-w64-mingw32-gcc
CFLAGS  = -Wall -Wextra -fno-builtin -Wl,--subsystem,10 -nostdlib -e efi_main -shared

target: $(TARGET)
	echo $(CFLAGS)

%.efi: *.c
	$(CC) $(CFLAGS) -o $@ $^
