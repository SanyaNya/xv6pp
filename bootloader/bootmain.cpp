#include "bootloader_new.hpp"
#include "bootloader_abort.hpp"
#include "../ELF/ELFHeader.hpp"
#include "../ELF/ProgramHeader.hpp"
#include "../libcpp/span.hpp"
#include "../io/irawstream.hpp"

namespace xv6pp
{

using irawstream = 
    io::basic_irawstream<
        char, std::char_traits<char>, 
        std::allocator<char>,
        true, true, true, true>;

extern "C" [[noreturn]] void bootmain()
{
    irawstream is(512);

    ELF::Header elf;
    is >> elf;
    
    is.seekg(512+elf.phoff);

    std::span phdrs(new ELF::Program::Header[elf.phnum], elf.phnum);
    is >> phdrs;

    for(auto& phdr : phdrs)
    {
        is.seekg(512 + phdr.offset);
        is.read(phdr.paddr, phdr.filesz);
    }

    elf.entry();
}

} //namespace xv6pp
