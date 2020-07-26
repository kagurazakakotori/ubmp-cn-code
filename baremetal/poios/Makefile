TARGET = poios.efi
USE_MOUSE = true

include ../baremetal.mk

.ONESHELL:
espcontent:
	mkdir -p ./esp
	cat << EOF | unix2dos | iconv -f UTF-8 -t UCS-2LE > ./esp/abc
	1234567890
	abcdefg
	blah blah blah
	EOF
	cp ./content/img.bgra ./esp/img

include ../../qemu.mk
include ../../run.mk
include ../../clean.mk
