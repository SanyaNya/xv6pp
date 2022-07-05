#ifndef ELF_HEADER_HPP
#define ELF_HEADER_HPP

#include "../libcpp/cstdint.hpp"
#include "Ident.hpp"

namespace ELF
{

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
    MIPS,
    PARISC,
    SPARC32PLUS,
    PPC,
    PPC64,
    S390,
    ARM,
    SH,
    SPARCV9,
    IA_64,
    X86_64,
    VAX
};

using EntryFunc = void(*)();

enum class Version : std::uint32_t { CURRENT = 1 };

constexpr std::uint16_t NO_PROGRAM_HEADER      = 0;
constexpr std::uint16_t NO_SECTION_HEADER      = 0;
constexpr std::uint16_t NO_SECTION_NAMES_TABLE = 0;

constexpr std::uint16_t PHNUM_MAX = 0xffff;
constexpr std::uint16_t PHNUM_PLUG = 0xffff;

constexpr std::uint16_t SHNUM_MAX = 0xff00;
constexpr std::uint16_t SHNUM_PLUG = 0;

constexpr std::uint16_t SHSTRNDX_MAX = 0xff00;
constexpr std::uint16_t SHSTRNDX_PLUG = 0xffff;

struct Header
{
    Ident::Struct ident;
    Type          type;
    ISA           machine;
    Version       version;
    EntryFunc     entry;
    std::uint32_t phoff;     //Program Header offset
                             //(relative to the begin of elf header).
                             //
                             //If file has no Program Header, phoff = NO_PROGRAM_HEADER

    std::uint32_t shoff;     //Section Header offset
                             //(relative to the begin of elf header).
                             //
                             //If file has no Section Header, shoff = NO_SECTION_HEADER
    
    std::uint32_t flags;     //Currently no flags defined
    std::uint16_t size;      //Size of this header
    std::uint16_t phentsize; //Size of Program Header`s table entry
                             //(all entries are the same size)
    
    std::uint16_t phnum;     //Count of Program Header`s entries.
                             //
                             //If file has no Program header, phnum = NO_PROGRAM_HEADER.
                             //
                             //If real phnum >= PHNUM_MAX,
                             //then phnum = PHNUM_PLUG
                             //and real phnum stored in
                             //sh_info member of first Section Header entry,
                             //otherwise sh_info = 0
    
    std::uint16_t shentsize; //Size of Section Header`s table entry
                             //(all entries are the same size)
    
    std::uint16_t shnum;     //Count of Section Header`s entries.
                             //
                             //If file has no Section Header, shnum = NO_SECTION_HEADER.
                             //
                             //If real shnum >= SHNUM_MAX,
                             //then shnum = SHNUM_PLUG
                             //and real shnum stored in sh_size member
                             //of first Section Header entry,
                             //otherwise sh_size = 0

    std::uint16_t shstrndx;  //Index of Section Header`s entry 
                             //that contains the section names.
                             //
                             //If file has no section names table,
                             //shstrndx = NO_SECTION_NAMES_TABLE.
                             //
                             //If real shstrndx >= SHSTRNDX_MAX,
                             //then shstrndx = SHSTRNDX_PLUG
                             //and real shstndx stored in sh_link member
                             //of first Section Header entry,
                             //otherwise sh_link = 0
};
 
} //namespace ELF

#endif //ELF_HEADER_HPP
