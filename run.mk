.ONESHELL:
bootimage: target
ifeq ($(USE_MOUSE), true)
	mkdir -p ./esp/EFI
	cp ./$(TARGET) ./esp/EFI/$(TARGET)
	cp ../../drivers/UsbMouseDxe.efi ./esp/EFI/UsbMouseDxe.efi
	cat << EOF > ./esp/startup.nsh
	load fs0:\EFI\UsbMouseDxe.efi
	.\EFI\$(TARGET)
	EOF
else
	mkdir -p ./esp/EFI/BOOT
	cp ./$(TARGET) ./esp/EFI/BOOT/BOOTX64.EFI
endif

esp: bootimage espcontent

run: esp qemu
