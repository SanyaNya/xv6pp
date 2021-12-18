#ifndef STD_BITSET_HPP
#define STD_BITSET_HPP

#include "cstddef.hpp"
#include "array.hpp"

namespace std
{

template<std::size_t N>
class bitset
{
public:
    class reference
    {
        friend class bitset;

        std::size_t& data;
        std::size_t  bit_pos;

        reference(std::size_t& bit, std::size_t pos)
            : data(bit), bit_pos(pos) {}

        reference& operator=(bool x) noexcept
        {
            data &= ~(1 << bit_pos);
            data |= x << bit_pos;
        }

    public:
        operator bool() const noexcept
        {
            return data & (1 << bit_pos);
        }

        bool operator~() const noexcept
        {
            return !static_cast<bool>(*this);
        }

        reference& flip() noexcept
        {
            data ^= 1 << bit_pos;
            return *this;
        }
    };


    constexpr bitset() noexcept = default;

    constexpr bitset(unsigned long long val) noexcept
        : data{ std::size_t(val) }
    {}

    //TODO string constructors

    constexpr bool operator[](std::size_t idx) const
    {
        return data[data_pos(idx)] & (1 << bit_pos(idx));
    }

    constexpr reference operator[](std::size_t idx)
    {
        return reference(data[data_pos(idx)], bit_pos(idx));
    }

private:
    static constexpr std::size_t data_count =
        N / sizeof(std::size_t) + 
        N % sizeof(std::size_t) == 0 ? 0 : 1;

    static constexpr std::size_t data_pos(std::size_t idx) noexcept
    {
        return idx / 8*sizeof(std::size_t);
    }

    static constexpr std::size_t bit_pos(std::size_t idx) noexcept
    {
        return (idx % 8*sizeof(std::size_t));
    }

    std::array<std::size_t, data_count> data;
};

} //namespace std

#endif //STD_BITSET_HPP
