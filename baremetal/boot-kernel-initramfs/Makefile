TARGET = boot-kernel-initramfs.efi
INITRAMFS_DIR = ../../linux/initramfs
INITRAMFS_IMG = $(INITRAMFS_DIR)/initramfs.img

include ../baremetal.mk

initramfs:
ifeq (,$(wildcard $(INITRAMFS_IMG)))
	cd $(INITRAMFS_DIR) && bash ./mkrootfs.sh
endif

espcontent:
	cp ../../linux/kernel/bzImage ./esp/bzImage.efi
	cp $(INITRAMFS_IMG) ./esp/initramfs.img

include ../../qemu.mk
include ../../run.mk
include ../../clean.mk
