#include "../libcpp/cstddef.hpp"
#include "ATA_PIO_LBA28_Disk.hpp"
#include "../ELF/ELFHeader.hpp"
#include "../ELF/ProgramHeader.hpp"
#include "bootloader_new.hpp"
#include "../libcpp/span.hpp"

namespace xv6pp
{

extern "C" void bootmain()
{
    ATA_PIO_LBA28_Disk<5120> disk;

    ELF::Header& elf = *new ELF::Header;
    disk >> elf;
    
    disk.seekg(512+elf.phoff);
    
    std::span phdrs(new ELF::Program::Header[elf.phnum], elf.phnum);
    for(auto& phdr : phdrs) disk >> phdr;

    for(auto& phdr : phdrs)
    {
        disk.seekg(512+phdr.offset);
        disk.read(phdr.paddr, phdr.filesz);
    }

    elf.entry();
}

} //namespace xv6pp
