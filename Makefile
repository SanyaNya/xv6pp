qemu_run:
	make -C bootloader
	qemu-system-x86_64 -fda bootloader/bootsector.bin

clean:
	make -C bootloader clean
