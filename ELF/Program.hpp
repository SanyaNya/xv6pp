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

enum class Flags : std::uint32_t
{
    X = 1, //Execute segment
    W = 2, //Write segment
    R = 4, //Read segment

    XW = 3,
    XR = 5,

    WR = 6,

    XWR = 7
};

struct Header
{
    Type type;
    std::uint32_t offset; //Offset from the beginning in the file image.
                          //Should be aligned according align member
    
    std::uint8_t* vaddr;  //Virtual address.
                          //Should be aligned according align member
    
    std::uint8_t* paddr;  //Physical address(on systems where is relevant)
    std::uint32_t filesz; //Size of the segment in the file
    std::uint32_t memsz;  //Size of the segment in memory
    Flags flags;
    std::uint32_t align;  //align should be positive and power of two
                          //if align = 0 or align = 1, then no alignment required
                          //offset % align = vaddr % align
                          //Loadable segments: offset % PAGE_SIZE = vaddr % PAGE_SIZE
};

} //namespace ELF::Program

#endif //ELF_PROGRAM_HPP
