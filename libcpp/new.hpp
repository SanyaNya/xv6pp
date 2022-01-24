#ifndef STD_NEW_HPP
#define STD_NEW_HPP

#include "cstddef.hpp"

//placement new
[[nodiscard]] inline void* operator new(std::size_t, void* p) noexcept
{
    return p;
}

[[nodiscard]] inline void* operator new[](std::size_t, void* p) noexcept
{
    return p;
}

inline void operator delete(void*, void*) noexcept {}
inline void operator delete[](void*, void*) noexcept {}

#endif //STD_NEW_HPP
