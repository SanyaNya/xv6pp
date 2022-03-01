#ifndef XV6PP_IO_BYTE_TRAITS_HPP
#define XV6PP_IO_BYTE_TRAITS_HPP

#include "../libcpp/cstddef.hpp"
#include "../libcpp/ios.hpp"

namespace xv6pp::io
{

struct byte_traits
{
    using char_type = std::byte;
    using int_type = int;
    using off_type = std::streamoff;
    using pos_type = std::streampos;
    using state_type = std::mbstate_t;

    static constexpr void assign(char_type& c1, const char_type& c2) noexcept
    {
        c1 = c2;
    }

    static constexpr bool eq(char_type c1, char_type c2) noexcept
    {
        return c1 == c2;
    }

    static constexpr bool eq_int_type(int_type c1, int_type c2) noexcept
    {
        return c1 == c2;
    }

    static constexpr bool lt(char_type c1, char_type c2) noexcept
    {
        return static_cast<unsigned char>(c1) < static_cast<unsigned char>(c2);
    }

    static constexpr int_type to_int_type(char_type c) noexcept
    {
        return static_cast<int_type>(static_cast<unsigned char>(c));
    }

    static constexpr char_type to_char_type(int_type i) noexcept
    {
        return static_cast<char_type>(i);
    }

    static constexpr int_type eof() noexcept
    {
        return -1;
    }

    static constexpr char_type* copy(char_type* dest, const char_type* src, std::size_t count)
    {
        std::copy(src, src+count, dest);
        return dest;
    }
};


} //namespace xv6pp::io

#endif //XV6PP_IO_BYTE_TRAITS_HPP
