#include "bootloader_new.hpp"
#include "bootloader_abort.hpp"
#include "../ELF/ELFHeader.hpp"
#include "../ELF/ProgramHeader.hpp"
#include "../libcpp/span.hpp"
#include "../io/irawstream.hpp"
#include "../io/byte_traits.hpp"
#include "gdtdesc.hpp"

namespace xv6pp
{

//To avoid code size overhead
//Turn off all checks
//Use fixed size buffer
//Use crtp for istream and streambuf
using irawstream = 
    io::basic_irawstream<
        std::byte, io::byte_traits, 
        std::allocator,
        true, true, true,
        4096, 4096, true>;

extern "C" [[noreturn]] void bootmain()
{
    irawstream is(512);

    ELF::Header elf;
    is >> elf;
    
    is.seekg(512 + elf.phoff);

    std::span phdrs(new ELF::Program::Header[elf.phnum], elf.phnum);
    is >> phdrs;

    for(const auto& phdr : phdrs)
    {
        is.seekg(512 + phdr.offset);
        is.read(phdr.paddr, phdr.filesz);
    }

    elf.entry();

    //In bootloader there is no need to free mem
}

} //namespace xv6pp
