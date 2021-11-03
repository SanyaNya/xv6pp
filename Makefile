qemu_run: bootloader/bootsector.bin
	make -C bootloader
	qemu-system-x86_64 -fda bootloader/bootsector.bin

clean:
	make -C bootloader clean
