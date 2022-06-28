#ifndef XV6PP_UTILS_BITFIELD_HELPER_FUNCTIONS_HPP
#define XV6PP_UTILS_BITFIELD_HELPER_FUNCTIONS_HPP

#include "../../libcpp/cstddef.hpp"
#include "../../libcpp/concepts.hpp"
#include "../../libcpp/limits.hpp"
#include "../../libcpp/utility.hpp"
#include "part.hpp"

namespace xv6pp::detail
{

template<std::integral T>
constexpr T lmask(std::size_t begin) noexcept
{
    return std::numeric_limits<T>::max() << begin;
}

template<std::integral T>
constexpr T rmask(std::size_t end) noexcept
{
    return std::numeric_limits<T>::max() >> 
	    (std::numeric_limits<T>::digits - end);
}

template<std::integral T>
constexpr T mask(std::size_t begin, std::size_t end) noexcept
{
    return lmask<T>(begin) & rmask<T>(end);
}

template<std::size_t SRC_POS, std::size_t DEST_POS, std::integral T>
constexpr T shift_to(T t) noexcept
{
    if constexpr(SRC_POS < DEST_POS)
        return t << (DEST_POS-SRC_POS);
    else
        return t >> (SRC_POS-DEST_POS);
}

} //namespace xv6pp::detail

#endif //XV6PP_UTILS_BITFIELD_HELPER_FUNCTIONS_HPP
