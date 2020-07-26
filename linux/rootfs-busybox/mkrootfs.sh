#!/bin/bash
BUSYBOX=./busybox
OUTPUT_FILE=rootfs.img
IMAGE_DIR=./rootfs

if [ -f ${OUTPUT_FILE} ]; then
    echo "${OUTPUT_FILE} already exists"
    exit
fi

if [ ! -f ${BUSYBOX} ]; then
    echo "${BUSYBOX} does not exist"
    exit
fi

# install busybox
mkdir -p ${IMAGE_DIR}/{bin,sbin,etc,lib,dev,proc,sys,usr}
mkdir -p ${IMAGE_DIR}/usr/{bin,sbin}
install -m 0750 -d ${IMAGE_DIR}/root
install -m 1777 -d ${IMAGE_DIR}/tmp
cp ./busybox ${IMAGE_DIR}/bin/busybox
for LINK_PATH in $(${BUSYBOX} --list-full); do
    ln -s /bin/busybox ${IMAGE_DIR}/${LINK_PATH}
done

# generate rcS
mkdir -p ${IMAGE_DIR}/etc/init.d
cat > ${IMAGE_DIR}/etc/init.d/rcS << EOF
#!/bin/sh
mount -t proc proc /proc
mount -t sysfs sysfs /sys
EOF
chmod -R 0755 ${IMAGE_DIR}/etc/init.d

# generate initramfs image
dd if=/dev/zero of=${OUTPUT_FILE} bs=1M count=32 status=none
mkfs.ext4 -q -d ${IMAGE_DIR} ${OUTPUT_FILE}

# cleanup
rm -rf ${IMAGE_DIR}
