#pragma once

#include "../libcpp/cstdint.hpp"
#include "../libcpp/cstddef.hpp"

namespace ELF::Ident
{

enum class Magic : std::uint32_t { value = 0x464c457f };

enum class Class : std::uint8_t
{
    C32, //32bit arch
    C64  //64bit arch
};

enum class Encoding : std::uint8_t
{
    NONE,
    LittleEndian,
    BigEndian
};

enum class Version : std::uint8_t
{
    CURRENT = 1
};

enum class ABI : std::uint8_t
{
    NONE,
    SYSV,
    HPUX,
    NETBSD,
    LINUX,
    SOLARIS,
    IRIX,
    FREEBSD,
    TRU64,
    ARM,
    STANDALONE
};

struct Struct
{
    Magic magic;
    Class clss;
    Encoding encoding;
    Version version;
    ABI abi;
    std::uint8_t abi_version;
    std::byte padding[7];
};

} //namespace ELF::Ident
