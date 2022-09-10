#pragma once

#include "cstddef_impl/types.hpp"

namespace std
{

enum class align_val_t : size_t {};

struct nothrow_t { explicit nothrow_t() = default; };
extern const nothrow_t nothrow;

template<typename T>
[[nodiscard]] constexpr T* launder(T* p) noexcept
{
    return __builtin_launder(p);
}

} //namespace std

[[nodiscard]] void* operator new(std::size_t);
[[nodiscard]] void* operator new(std::size_t, std::align_val_t);
[[nodiscard]] void* operator new(std::size_t, const std::nothrow_t&) noexcept;
[[nodiscard]] void* operator new(std::size_t, std::align_val_t, const std::nothrow_t&) noexcept;


[[nodiscard]] void* operator new[](std::size_t);
[[nodiscard]] void* operator new[](std::size_t, std::align_val_t);
[[nodiscard]] void* operator new[](std::size_t, const std::nothrow_t&) noexcept;
[[nodiscard]] void* operator new[](std::size_t, std::align_val_t, const std::nothrow_t&) noexcept;


void operator delete(void*) noexcept;
void operator delete(void*, std::size_t) noexcept;
void operator delete(void*, std::align_val_t) noexcept;
void operator delete(void*, std::size_t, std::align_val_t) noexcept;
void operator delete(void*, const std::nothrow_t&) noexcept;
void operator delete(void*, std::align_val_t, const std::nothrow_t&) noexcept;

void operator delete[](void*) noexcept;
void operator delete[](void*, std::size_t) noexcept;
void operator delete[](void*, std::align_val_t) noexcept;
void operator delete[](void*, std::size_t, std::align_val_t) noexcept;
void operator delete[](void*, const std::nothrow_t&) noexcept;
void operator delete[](void*, std::align_val_t, const std::nothrow_t&) noexcept;



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
