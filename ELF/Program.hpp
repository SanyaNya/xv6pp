#ifndef ELF_PROGRAM_HPP
#define ELF_PROGRAM_HPP

#include "../libcpp/cstdint.hpp"

namespace ELF::Program
{

enum class Type : std::uint32_t
{
    NULL    = 0x0,        //Unused
    LOAD    = 0x1,        //Loadable segment
    DYNAMIC = 0x2,        //Dynamic linking info
    INTERP  = 0x3,        //Interpreter info
    NOTE    = 0x4,        //Auxillary info
    SHLIB   = 0x5,        //Reserved
    PHDR    = 0x6,        //Segment containing Program Header itself
    TLS     = 0x7,        //Thread-Local Storage template
    LOOS    = 0x60000000, //Reserved range for OS - low
    HIOS    = 0x6fffffff, //Reserved range for OS - high
    LOPROC  = 0x70000000, //Reserved range for Processor - low
    HIPROC  = 0x7fffffff  //Reserved range for Processor - high
};

struct Header
{
    Type type;
    std::uint32_t offset; //Offset in the file image
    std::uint8_t* vaddr;  //virtual address
    std::uint8_t* paddr;  //physical address(on systems where is relevant)
    std::uint32_t filesz; //size of the segment in the file
    std::uint32_t memsz;  //size of the segment in memory
    std::uint32_t flags;
    std::uint32_t p_align;
};

} //namespace ELF::Program

#endif //ELF_PROGRAM_HPP
