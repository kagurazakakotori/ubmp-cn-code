TARGET = boot-kernel-rootfs.efi
MOUNT_ROOTFS = true
ROOTFS_DIR = ../../linux/rootfs-busybox
ROOTFS_IMG = $(ROOTFS_DIR)/rootfs.img

include ../baremetal.mk

rootfs:
ifeq (,$(wildcard $(ROOTFS_IMG)))
	cd $(ROOTFS_DIR) && bash ./mkrootfs.sh
endif

espcontent: rootfs
	cp ../../linux/kernel/bzImage ./esp/bzImage.efi

include ../../qemu.mk
include ../../run.mk
include ../../clean.mk
