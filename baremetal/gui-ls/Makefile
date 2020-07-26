TARGET = gui-ls.efi
USE_MOUSE = true

include ../baremetal.mk

.ONESHELL:
espcontent:
	mkdir -p ./esp
	touch ./esp/abc ./esp/123

include ../../qemu.mk
include ../../run.mk
include ../../clean.mk
