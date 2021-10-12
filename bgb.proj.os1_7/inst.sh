# mkfs.msdos /dev/fd0
mount /dev/fd0 /mnt/r0 -t vfat
cp bin/x86/setup /mnt/r0/setup.bin
cp bin/x86/kernel /mnt/r0/kernel.bin
cp root/* /mnt/r0

umount /mnt/r0

#hacked, works around some bug in dd?
dd if=bin/x86/boot_fat of=/dev/fd0 bs=3 count=1
dd if=/dev/fd0 of=tmp bs=62 count=1
dd if=bin/x86/boot_fat of=/dev/fd0 bs=512 count=1
dd if=tmp of=/dev/fd0 bs=62 count=1
