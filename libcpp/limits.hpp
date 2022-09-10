#pragma once

namespace std
{

template<typename T>
struct numeric_limits
{
    static constexpr bool is_specialized = false;
};

template<>
struct numeric_limits<unsigned long>
{
    static constexpr bool is_specialized = true;
    
    static constexpr unsigned long min() noexcept
    {
        return 0;
    }

    static constexpr unsigned long max() noexcept
    {
        return 0xfffffffful;
    }

    static constexpr int digits = 32;
};

template<>
struct numeric_limits<unsigned int>
{
    static constexpr bool is_specialized = true;
    
    static constexpr unsigned int min() noexcept
    {
        return 0u;
    }

    static constexpr unsigned int max() noexcept
    {
        return 0xffffffffu;
    }

    static constexpr int digits = 32;
};

template<>
struct numeric_limits<unsigned long long>
{
    static constexpr bool is_specialized = true;

    static constexpr unsigned long long min() noexcept
    {
        return 0ull;
    }

    static constexpr unsigned long long max() noexcept
    {
        return 0xffffffffffffffffull;
    }

    static constexpr int digits = 64;
};


template<>
struct numeric_limits<unsigned char>
{
    static constexpr bool is_specialized = true;
    
    static constexpr unsigned char min() noexcept
    {
        return 0;
    }

    static constexpr unsigned char max() noexcept
    {
        return 0xff;
    }

    static constexpr int digits = 8;
};

} //namespace std
