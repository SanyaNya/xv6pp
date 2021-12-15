#include "../libcpp/cstddef.hpp"
#include "ATA_PIO_LBA28_Disk.hpp"
#include "../ELF/ELFHeader.hpp"
#include "../ELF/ProgramHeader.hpp"

static ATA_PIO_LBA28_Disk disk;

static ELF::Header& elf = *reinterpret_cast<ELF::Header*>(0x10000);

extern "C" void bootmain()
{
    disk >> elf;
    
    disk.seekg(elf.phoff - sizeof(ELF::Header));
    
    ELF::Program::Header* phdr =
        reinterpret_cast<ELF::Program::Header*>(0x10000+sizeof(ELF::Header)); 

    for(std::size_t i = 0; i != elf.phnum; ++i, ++phdr)
        disk >> phdr;

    elf.entry();
}
