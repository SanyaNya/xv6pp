#ifndef STD_NEW_HPP
#define STD_NEW_HPP

#include "cstddef.hpp"

namespace std
{

enum class align_val_t : size_t {};

} //namespace std

[[nodiscard]] void* operator new(std::size_t);
[[nodiscard]] void* operator new(std::size_t, std::align_val_t);

void operator delete(void*) noexcept;
void operator delete(void*, std::size_t) noexcept;
void operator delete(void*, std::align_val_t) noexcept;

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
