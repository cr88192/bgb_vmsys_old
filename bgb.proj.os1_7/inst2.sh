# mkfs.msdos /dev/fd0
cp -uv bin/x86/setup /cygdrive/a/setup.bin
cp -uv bin/x86/kernel.sys /cygdrive/a

#cp -uv \
#	root/* \
#	apps/*.exe \
#	\
#	/cygdrive/a

dd if=bin/x86/boot_fat of=/dev/fd0 bs=512 count=1
