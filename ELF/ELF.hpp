#ifndef ELF_HPP
#define ELF_HPP

#include "../libcpp/cstdint.hpp"

namespace ELF
{

enum class Magic : std::uint32_t { value = 0x464c457f };

enum class Type : std::uint16_t
{
    NONE   = 0x00,
    REL    = 0x01,
    EXEC   = 0x02,
    DYN    = 0x03,
    CORE   = 0x04,
    LOOS   = 0xfe00,
    HIOS   = 0xfeff,
    LOPROC = 0xff00,
    HIPROC = 0xffff
};

enum class ISA : std::uint16_t
{
    NONE,
    M32,
    SPARC,
    I386,
    M68K,
    M88K,
    I860,
    MIPS
};

using EntryFunc = void(*)();

enum class Version : std::uint32_t { value = 1 };

struct Header
{
    Magic         magic;
    std::uint8_t  elf[12];   //skip
    Type          type;
    ISA           machine;
    Version       version;
    EntryFunc     entry;
    std::uint32_t phoff;     //Program Header offset(relative to the begin of elf header)
    std::uint32_t shoff;     //Section Header offset(relative to the begin of elf header)
    std::uint32_t flags;     //TODO make enum
    std::uint16_t size;      //Size of this header
    std::uint16_t phentsize; //Size of Program Header`s table entry
    std::uint16_t phnum;     //Count of Program Header`s entries
    std::uint16_t shentsize; //Size of Section Header`s table entry
    std::uint16_t shnum;     //Count of Section Header`s entries
    std::uint16_t shstrndx;  //Index of Section Header`s entry that contains the section names
};

}

#endif //ELF_HPP
