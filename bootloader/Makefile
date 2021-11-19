bootsector.bin: boot.bin
	make -C bootsector_creator
	./bootsector_creator/create_bootsector

boot.o: bootloader.asm
	nasm -f elf32 bootloader.asm -o boot.o

boot.bin: boot.o bootmain.cpp linker.ld
	i386-elf-g++ -std=c++20 -Os bootmain.cpp boot.o -o boot.bin -nostdlib -ffreestanding -mno-red-zone -fno-exceptions -fno-rtti -Wall -Wextra -Werror -T linker.ld
	echo "kernel size: $(wc -c < boot.bin) bytes"

clean:
	rm boot.o boot.bin bootsector.bin
	make -C bootsector_creator clean
