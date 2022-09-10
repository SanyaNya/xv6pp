#pragma once

#include <cstdint>
#include <cstddef>
#include "utils/bitfield/bitfield.hpp"

namespace ELF::Section
{

enum class Type : std::uint32_t
{
    NULL,     //Inactive, other members undefined
    PROGBITS, //Info about program
    SYMTAB,   //Symbol Table
    STRTAB,   //String Table
    RELA,     //Relocation entries with explicit addends
    HASH,     //Symbol hash table
    DYNAMIC,  //Dynamic linking info
    NOTE,     //Notes
    NOBITS,   //Like PROGBITS but occupies no space in the file
    REL,      //Relocation offsets without explicit addends
    SHLIB,    //RESERVED
    DYNSYM,   //Set of dynamic linking symbols
    
    LOPROC = 0x70000000, //RESERVED for processor specific
    HIPROC = 0x7fffffff, //

    LOUSER = 0x80000000, //RESERVED for application
    HIUSER = 0xffffffff  //

};

struct Flags : xv6pp::bitfield<Flags, std::uint32_t>
{
    using bitfield::bitfield;

    std::uint32_t WRITE     : 1;
    std::uint32_t ALLOC     : 1;
    std::uint32_t EXECINSTR : 1;

    std::uint32_t : 25;

    std::uint32_t PROC0 : 1;
    std::uint32_t PROC1 : 1;
    std::uint32_t PROC2 : 1;
    std::uint32_t PROC3 : 1;
};

struct Header
{
    std::uint32_t name_idx;
    Type          type;
    Flags         flags;
    std::byte* addr;      //If section don`t appears in the memory addr = 0
    std::uint32_t offset; //Offset from the beginning of the file
    std::uint32_t size;   //Size of this section.
    std::uint32_t link;   //Section Header table index(interpretation depends on section type)
    std::uint32_t info;   //Extra info(interpretation depends on section type)
    std::uint32_t align;  //align should be positive and power of two
                          //if align = 0 or align = 1, then no alignment required

    std::uint32_t entsize; //Size of entry in table.
                           //If entsize = 0, there is no table
};

} //namespace ELF::Section
