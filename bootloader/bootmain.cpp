#include "bootloader_new.hpp"
#include "bootloader_abort.hpp"
#include "../ELF/ELFHeader.hpp"
#include "../ELF/ProgramHeader.hpp"
#include "../libcpp/span.hpp"
#include "../io/rawbuf.hpp"
#include "../libcpp/istream.hpp"

namespace xv6pp
{

using rawbuf = 
    io::basic_rawbuf<
        char, std::char_traits<char>, 
        std::allocator<char>, 
        true>;

using istream = 
    std::basic_istream<
        char, std::char_traits<char>, 
        true, true, int, rawbuf>;

extern "C" [[noreturn]] void bootmain()
{
    rawbuf rbuf(512);
    istream is(&rbuf);

    ELF::Header elf;
    is.read(reinterpret_cast<char*>(&elf), sizeof(ELF::Header));
    
    is.seekg(512+elf.phoff);

    std::span phdrs(new ELF::Program::Header[elf.phnum], elf.phnum);
    is.read(reinterpret_cast<char*>(phdrs.data()), phdrs.size_bytes());

    for(auto& phdr : phdrs)
    {
        is.seekg(512 + phdr.offset);
        is.read(reinterpret_cast<char*>(phdr.paddr), phdr.filesz);
    }

    elf.entry();
}

} //namespace xv6pp
