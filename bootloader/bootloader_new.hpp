#ifndef XV6PP_BOOTLOADER_NEW_HPP
#define XV6PP_BOOTLOADER_NEW_HPP

#include "../libcpp/new.hpp"
#include "../libcpp/cstddef.hpp"

namespace xv6pp
{

namespace detail
{

extern "C" unsigned char BOOTMAGIC_ADDR[];

inline unsigned char* free_mem = BOOTMAGIC_ADDR;

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

[[nodiscard]] void* operator new[](std::size_t size)
{
   return xv6pp::detail::alloc(size);
}

void operator delete(void*) noexcept {}
void operator delete[](void*) noexcept {}
void operator delete(void*, std::size_t) {}
void operator delete[](void*, std::size_t) {}

#endif //XV6PP_BOOTLOADER_NEW_HPP
