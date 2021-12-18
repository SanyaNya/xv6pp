#ifndef EBITSET_HPP
#define EBITSET_HPP

#include "../libcpp/bitset.hpp"
#include "../libcpp/type_traits.hpp"

template<std::size_t N, typename E>
    requires std::is_enum_v<E>
struct ebitset : std::bitset<N>
{
    ebitset() noexcept = default;
    ebitset(unsigned long long x) noexcept : std::bitset<N>(x) {}

    constexpr bool operator[](E e) const
    {
        return static_cast<const std::bitset<N>*>(this)->operator[](std::to_underlying(e));
    }

    constexpr typename std::bitset<N>::reference operator[](E e)
    {
        return static_cast<std::bitset<N>*>(this)->operator[](std::to_underlying(e));
    }
};

#endif //EBITSET_HPP
