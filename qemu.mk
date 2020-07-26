OVMF_PATH = /usr/share/OVMF/OVMF_CODE.fd
QEMU_OPTS = -bios $(OVMF_PATH) -vga std -net none -drive file=fat:rw:esp,index=0,format=vvfat

ifneq ($(wildcard /dev/kvm),)
	KVM = -enable-kvm
endif

ifeq ($(USE_MOUSE), true)
	QEMU_OPTS += -usb -device usb-mouse
endif

ifeq ($(MOUNT_ROOTFS), true)
	QEMU_OPTS += -drive file=$(ROOTFS_IMG),index=1,format=raw
endif

qemu:
	qemu-system-$(ARCH) $(KVM) $(QEMU_OPTS)

