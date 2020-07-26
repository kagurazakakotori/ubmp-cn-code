TARGET = boot-kernel.efi

include ../baremetal.mk

espcontent:
	cp ../../linux/kernel/bzImage ./esp/bzImage.efi

include ../../qemu.mk
include ../../run.mk
include ../../clean.mk
