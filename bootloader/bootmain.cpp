#include "ATA_PIO_LBA28_Disk.hpp"
#include "../ELF/ELF.hpp"

static ATA_PIO_LBA28_Disk disk;

extern "C" void bootmain()
{
    ELF::Header elf;
    disk >> elf;
}
