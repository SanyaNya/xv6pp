#pragma once

#include "../algorithm.hpp"
#include "../ios_impl/types.hpp"

namespace std
{

template<typename CharT>
struct char_traits;

template<>
struct char_traits<char>
{
    using char_type = char;
    using int_type = int;
    using off_type = streamoff;
    using pos_type = streampos;
    using state_type = mbstate_t;

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

} //namespace std
