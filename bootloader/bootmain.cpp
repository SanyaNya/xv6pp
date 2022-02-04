#include "bootloader_new.hpp"
#include "../ELF/ELFHeader.hpp"
#include "../ELF/ProgramHeader.hpp"
#include "../libcpp/span.hpp"
#include "../io/raw_streambuf.hpp"

namespace xv6pp
{

extern "C" [[noreturn]] void bootmain()
{
    io::rawbuf rbuf(512);

    ELF::Header elf;
    rbuf.sgetn(reinterpret_cast<char*>(&elf), sizeof(ELF::Header));
    
    rbuf.pubseekpos(512+elf.phoff);

    std::span phdrs(new ELF::Program::Header[elf.phnum], elf.phnum);
    for(auto& phdr : phdrs) 
        rbuf.sgetn(reinterpret_cast<char*>(&phdr), sizeof(ELF::Program::Header));

    for(auto& phdr : phdrs)
    {
        rbuf.pubseekpos(512 + phdr.offset);
        rbuf.sgetn(reinterpret_cast<char*>(phdr.paddr), phdr.filesz);
    }

    elf.entry();
}

} //namespace xv6pp
