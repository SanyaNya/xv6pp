#pragma once

#include "../meta/fundamental_types.hpp"
#include "type_traits_impl/make_unsigned.hpp"
#include "limits.hpp"

namespace std
{

namespace detail
{

using stdint_types = meta::signed_int_types::push_front<signed char>;

template<typename T>
constexpr auto bit_size_v = 
    std::numeric_limits<unsigned char>::digits * sizeof(T);

template<auto SIZE>
using stdint_equal_bit_size_t = 
    stdint_types::find_type_if<
        []<typename T>(){ return bit_size_v<T> == SIZE; }>;

template<auto SIZE>
using stdint_least_bit_size_t = 
    stdint_types::find_type_if<
        []<typename T>(){ return bit_size_v<T> >= SIZE; }>;

} //namespace detail


    using int8_t  = detail::stdint_equal_bit_size_t<8>;
    using int16_t = detail::stdint_equal_bit_size_t<16>;
    using int32_t = detail::stdint_equal_bit_size_t<32>;
    using int64_t = detail::stdint_equal_bit_size_t<64>;

    using int_least8_t  = detail::stdint_least_bit_size_t<8>;
    using int_least16_t = detail::stdint_least_bit_size_t<16>;
    using int_least32_t = detail::stdint_least_bit_size_t<32>;
    using int_least64_t = detail::stdint_least_bit_size_t<64>;

    using intmax_t = 
        detail::stdint_types::max<
            []<typename A, typename B>()
            { return (sizeof(A) > sizeof(B)); }>;

    using intptr_t =
        detail::stdint_types::find_type_if<
            []<typename T>(){ return sizeof(T) == sizeof(void*); }>;


    using uint8_t  = make_unsigned_t<int8_t>;
    using uint16_t = make_unsigned_t<int16_t>;
    using uint32_t = make_unsigned_t<int32_t>;
    using uint64_t = make_unsigned_t<int64_t>;

    using uint_least8_t  = make_unsigned_t<int8_t>;
    using uint_least16_t = make_unsigned_t<int16_t>;
    using uint_least32_t = make_unsigned_t<int32_t>;
    using uint_least64_t = make_unsigned_t<int64_t>;

    using uintmax_t = make_unsigned_t<intmax_t>;

    using uintptr_t = make_unsigned_t<intptr_t>;

} //namespace std
