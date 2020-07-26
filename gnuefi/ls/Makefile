TARGET = ls.efi

include ../gnuefi.mk

.ONESHELL:
espcontent:
	mkdir -p ./esp
	touch ./esp/abc ./esp/123

include ../../qemu.mk
include ../../run.mk
include ../../clean.mk
