#ifndef XV6PP_BOOTLOADER_NEW_HPP
#define XV6PP_BOOTLOADER_NEW_HPP

#include "../libcpp/new.hpp"
#include "../libcpp/cstddef.hpp"
#include "../libcpp/type_traits_impl/underlying_type.hpp"

namespace xv6pp
{

namespace detail
{

extern "C" unsigned char BOOTMAGIC_ADDR[];

inline unsigned char* free_mem = BOOTMAGIC_ADDR;

inline void align(std::align_val_t align)
{
    free_mem += 
        reinterpret_cast<std::underlying_type_t<std::align_val_t>>(free_mem) %        std::to_underlying(align);
}

inline void* alloc(std::size_t size)
{
    void* r = xv6pp::detail::free_mem;
    xv6pp::detail::free_mem += size;
    return r;
}

} //namespace detail

} //namesapce xv6pp

[[nodiscard]] void* operator new(std::size_t size)
{
    return xv6pp::detail::alloc(size);
}

[[nodiscard]] void* operator new(std::size_t size, std::align_val_t align)
{
    xv6pp::detail::align(align);
    return ::operator new(size);
}

[[nodiscard]] void* operator new[](std::size_t size)
{
    return ::operator new(size);
}

[[nodiscard]] void* operator new[](std::size_t size, std::align_val_t align)
{
    return ::operator new(size, align);
}

void operator delete(void*) noexcept {}
void operator delete[](void*) noexcept {}
void operator delete(void*, std::size_t) {}
void operator delete[](void*, std::size_t) {}

#endif //XV6PP_BOOTLOADER_NEW_HPP
