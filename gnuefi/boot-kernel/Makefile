TARGET = boot-kernel.efi

include ../gnuefi.mk

espcontent:
	cp ../../linux/kernel/bzImage ./esp/bzImage

include ../../qemu.mk
include ../../run.mk
include ../../clean.mk
