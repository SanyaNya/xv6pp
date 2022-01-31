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
        const std::size_t bpos;

        reference(std::size_t& bit, std::size_t pos)
            : data(bit), bpos(pos) {}

        reference& operator=(bool x) noexcept
        {
            data &= ~bit_mask(bpos);
            data |= std::size_t(x) << bpos;
        }

    public:
        operator bool() const noexcept
        {
            return data & bit_mask(bpos);
        }

        bool operator~() const noexcept
        {
            return !static_cast<bool>(*this);
        }

        reference& flip() noexcept
        {
            data ^= bit_mask(bpos);
            return *this;
        }
    };


    constexpr bitset() noexcept = default;

    constexpr bitset(unsigned long long val) noexcept
        : data{ size_t(val) } {}

    //TODO string constructors

    constexpr bool operator[](std::size_t idx) const
    {
        return data[word_pos(idx)] & bit_pos_mask(idx);
    }

    constexpr reference operator[](std::size_t idx)
    {
        return reference(data[word_pos(idx)], bit_pos(idx));
    }

private:
    static constexpr std::size_t WORD_BIT_SIZE = 8*sizeof(std::size_t);

    static constexpr std::size_t WORD_COUNT =
        N / WORD_BIT_SIZE + 
        N % WORD_BIT_SIZE == 0 ? 0 : 1;

    static constexpr std::size_t word_pos(std::size_t idx) noexcept
    {
        return idx / WORD_BIT_SIZE;
    }

    static constexpr std::size_t bit_pos(std::size_t idx) noexcept
    {
        return idx % WORD_BIT_SIZE;
    }

    static constexpr std::size_t bit_mask(std::size_t idx) noexcept
    {
        return std::size_t(1) << idx;
    }

    static constexpr std::size_t bit_pos_mask(std::size_t idx) noexcept
    {
        return bit_mask(bit_pos(idx));
    }

    std::array<std::size_t, WORD_COUNT> data;
};

} //namespace std

#endif //STD_BITSET_HPP
