#pragma once

namespace std
{

template<typename T, T v>
struct integral_constant
{
    using value_type = T;
    using type = integral_constant;

    static constexpr T value = v;
    
    constexpr operator value_type() const noexcept
    {
        return value;
    }

    constexpr value_type operator()() const noexcept
    {
        return value;
    }
};

} //namespace std
