#ifndef STD_LIMITS_HPP
#define STD_LIMITS_HPP

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
        return 4294967295ul;
    }
};

template<>
struct numeric_limits<unsigned int>
{
    static constexpr bool is_specialized = true;
    
    static constexpr unsigned int min() noexcept
    {
        return 0;
    }

    static constexpr unsigned int max() noexcept
    {
        return 4294967295u;
    }
};

} //namespace std

#endif //STD_LIMITS_HPP
