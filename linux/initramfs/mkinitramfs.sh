#!/bin/bash
OUTPUT_FILE=initramfs.img

if [ -f ${OUTPUT_FILE} ]; then
    echo "${OUTPUT_FILE} already exists"
    exit
fi

mkinitramfs -d ./ -o ${OUTPUT_FILE} 2> /dev/null
