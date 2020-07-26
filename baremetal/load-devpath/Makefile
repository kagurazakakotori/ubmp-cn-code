TARGET = load-devpath.efi

include ../baremetal.mk

espcontent:
	$(MAKE) -C ../hello
	cp ../hello/hello.efi ./esp/test.efi

include ../../qemu.mk
include ../../run.mk
include ../../clean.mk
