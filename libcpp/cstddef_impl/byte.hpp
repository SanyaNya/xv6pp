#ifndef STD_CSTDDEF_IMPL_BYTE_HPP
#define STD_CSTDDEF_IMPL_BYTE_HPP

#include "../concepts_impl/integral.hpp"
#include "../type_traits_impl/underlying_type.hpp"

namespace std
{

enum class byte : unsigned char {};

template<integral IntType>
constexpr byte operator<<(byte b, IntType shift) noexcept
{
    return static_cast<byte>(
            static_cast<underlying_type_t<byte>>(
                static_cast<unsigned int>(b) << shift));
}

template<integral IntType>
constexpr byte& operator<<=(byte& b, IntType shift) noexcept
{
    return b = b << shift;
}

template<integral IntType>
constexpr byte operator>>(byte b, IntType shift) noexcept
{
    return static_cast<byte>(
            static_cast<underlying_type_t<byte>>(
                static_cast<unsigned int>(b) >> shift));
}

template<integral IntType>
constexpr byte& operator>>=(byte& b, IntType shift) noexcept
{
    return b = b >> shift;
}

constexpr byte operator|(byte l, byte r) noexcept
{
    return static_cast<byte>(
            static_cast<underlying_type_t<byte>>(
                static_cast<unsigned int>(l) | static_cast<unsigned int>(r)));
}

constexpr byte& operator|=(byte& l, byte r) noexcept
{
    return l = l | r;
}

constexpr byte operator&(byte l, byte r) noexcept
{
    return static_cast<byte>(
            static_cast<underlying_type_t<byte>>(
                static_cast<unsigned int>(l) & static_cast<unsigned int>(r)));
}

constexpr byte& operator&=(byte& l, byte r) noexcept
{
    return l = l & r;
}

constexpr byte operator^(byte l, byte r) noexcept
{
    return static_cast<byte>(
            static_cast<underlying_type_t<byte>>(
                static_cast<unsigned int>(l) ^ static_cast<unsigned int>(r)));
}

constexpr byte& operator^=(byte& l, byte r) noexcept
{
    return l = l ^ r;
}

constexpr byte operator~(byte b) noexcept
{
    return static_cast<byte>(
            static_cast<underlying_type_t<byte>>(
                ~static_cast<unsigned int>(b)));
}

template<integral IntType>
constexpr IntType to_integer(byte b) noexcept
{
    return static_cast<IntType>(b);
}

} //namespace std

#endif //STD_CSTDDEF_IMPL_BYTE_HPP
