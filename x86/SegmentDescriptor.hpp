#pragma once

#include "../utils/bitfield.hpp"
#include "../advanced-bitfield/advanced_bitfield.hpp"

namespace xv6pp::x86::Segment
{

enum class Type : std::uint8_t
{
    Data,
    Code
};

enum class Readable : std::uint8_t
{
    No,
    Yes
};

enum class Writable : std::uint8_t
{
    No,
    Yes
};

enum class ConformingPrivilege : std::uint8_t
{
    Equal_Ring,
    EqualLess_Ring
};

enum class Privilege : std::uint8_t
{
    Kernel = 0,
    User = 3
};

enum class Direction : std::uint8_t
{
    Up,
    Down
};

template<Type type>
struct Access;

template<>
struct Access<Type::Code> : bitfield<Access<Type::Code>, std::uint8_t>
{
    using bitfield::bitfield;

    bool                accessed             : 1 = 0;
    Readable            readable             : 1;
    ConformingPrivilege conforming_privilege : 1;
    Type                type                 : 1 = Type::Code;
    bool                _                    : 1 = 1;
    Privilege           privilege            : 2;
    bool                present              : 1 = 1;

    constexpr Access(Readable read, ConformingPrivilege conf, Privilege privil)
        : readable(read),
          conforming_privilege(conf),
          privilege(privil) {}
};

template<>
struct Access<Type::Data> : bitfield<Access<Type::Data>, std::uint8_t>
{
    using bitfield::bitfield;

    bool      accessed   : 1 = 0;
    Writable  writable   : 1;
    Direction direction  : 1;
    Type      type       : 1 = Type::Data;
    bool      _          : 1 = 1;
    Privilege privilege  : 2;
    bool      present    : 1 = 1;

    constexpr Access(Writable write, Direction dir, Privilege privil)
        : writable(write),
          direction(dir),
          privilege(privil) {}
};

enum class Size : std::uint8_t
{
    bit16,
    bit32
};

enum class LimitGranularity : std::uint8_t
{
    byte1,
    kib4
};

struct Flags : bitfield<Flags, std::uint8_t>
{
    using bitfield::bitfield;

    bool avl                     : 1 = 0;
    bool longmode                : 1 = 0;
    Size size                    : 1;
    LimitGranularity granularity : 1;
    std::uint8_t _               : 4 = 0;
    
    constexpr Flags(Size s, LimitGranularity lg) noexcept :
        size(s), granularity(lg) {}
};

template<Type type>
class Descriptor : public abf::bitfield<Descriptor<type>, std::uint64_t>
{
    using bf = abf::bitfield<Descriptor<type>, std::uint64_t>;
    using bf::bf;

public:
    ABF_FIELD(bf, 
        std::uint32_t, base,   16, 32,
                               32, 40,
                               56, 64)

    ABF_FIELD(bf, 
        std::uint32_t, lim,     0, 16, 
                               48, 52)

    ABF_FIELD(bf, 
        Access<type>,  access, 40, 48)

    ABF_FIELD(bf, 
        Flags,         flags,  52, 56)

    constexpr Descriptor(base_b b, lim_b l, access_b a, flags_b f) 
        noexcept : ABF_CTOR(bf, b, l, a, f) {}
};

template<typename T>
concept IsDescriptor = 
    std::is_same_v<std::remove_cvref_t<T>, Descriptor<Type::Code>> || 
    std::is_same_v<std::remove_cvref_t<T>, Descriptor<Type::Data>>;

} //namespace xv6pp::x86::Segment
