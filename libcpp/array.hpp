#ifndef STD_ARRAY_HPP
#define STD_ARRAY_HPP

#include "cstddef.hpp"

namespace std
{

template<typename T, std::size_t N>
struct array
{
    using value_type      = T;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using iterator        = value_type*;
    using const_iterator  = const value_type*;
    //using reverse_iterator =       //TODO
    //using const_reverse_iterator = //

    value_type __array[N];

    constexpr reference operator[](size_type idx)
    {
        return __array[idx];
    }

    constexpr const_reference operator[](size_type idx) const
    {
        return __array[idx];
    }

    constexpr pointer data() noexcept
    {
        return __array;
    }

    constexpr const_pointer data() const noexcept
    {
        return __array;
    }

    constexpr iterator begin() noexcept
    {
        return __array;
    }

    constexpr const_iterator cbegin() const noexcept
    {
        return __array;
    }

    constexpr iterator end() noexcept
    {
        return __array+N;
    }

    constexpr const_iterator cend() const noexcept
    {
        return __array+N;
    }

    constexpr size_type size() const noexcept
    {
        return N;
    }

    //TODO
    //...
};

} //namespace std

#endif //STD_ARRAY_HPP
