nasm -f elf32 bootloader.asm -o boot.o
i386-elf-g++ -std=c++20 kmain.cpp boot.o -o kernel.bin -nostdlib -ffreestanding -mno-red-zone -fno-exceptions -fno-rtti -Wall -Wextra -Werror -T linker.ld
echo "kernel size: $(wc -c < kernel.bin) bytes"
./create_kernel_bootsector
