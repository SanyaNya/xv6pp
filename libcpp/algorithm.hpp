#ifndef STD_ALGORITHM_HPP
#define STD_ALGORITHM_HPP

#include "type_traits_impl/is_nothrow_move_constructible.hpp"
#include "type_traits_impl/is_nothrow_move_assignable.hpp"
#include "cstring.hpp"

namespace std
{

template<typename InputIt, typename OutputIt>
constexpr OutputIt copy(InputIt src_first, InputIt src_last, OutputIt dest_first)
{
    return static_cast<OutputIt>(memcpy(dest_first, src_first, src_last-src_first));
}

template<typename T>
constexpr void swap(T& a, T& b) 
    noexcept(
        is_nothrow_move_constructible_v<T> &&
        is_nothrow_move_assignable_v<T>)
{
    T tmp = move(a);
    a = move(b);
    b = move(tmp);
}

template<typename T, size_t N>
constexpr void swap(T (&a)[N], T (&b)[N]) noexcept(noexcept(swap(*a, *b)))
{
    for(size_t i = 0; i != N; ++i)
        swap(a[i], b[i]);
}

template<typename T>
constexpr const T& min(const T& a, const T& b)
{
    return a < b ? a : b;
}

} //namespace std

#endif //STD_ALGORITHM_HPP
