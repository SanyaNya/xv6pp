#pragma once

#include "../libcpp/type_traits.hpp"
#include "../libcpp/concepts.hpp"
#include "../libcpp/cstddef.hpp"
#include "../libcpp/cstdint.hpp"

namespace xv6pp::x86
{

template<
    std::explicitly_convertible_to<std::uint16_t> E, 
    std::explicitly_convertible_to<std::uint8_t>  T>
inline void outb(E port, T data)
{
    asm volatile("out %0,%1" : : 
                 "a" (static_cast<std::uint8_t>(data)), 
                 "d" (static_cast<std::uint16_t>(port)));
}

template<std::explicitly_convertible_to<std::uint16_t> E>
inline std::byte inb(E port)
{
    std::byte data;

    asm volatile("in %1,%0" : 
                 "=a" (data) : 
                 "d" (static_cast<std::uint16_t>(port)));

    return data;
}

template<std::explicitly_convertible_to<std::uint16_t> E, typename T>
inline void insl(E port, T* dest, std::size_t count)
{
    asm volatile("cld; rep insl" :
                 "=D" (dest), "=c" (count) :
                 "d" (static_cast<std::uint16_t>(port)), 
                 "0" (dest), "1" (count) :
                 "memory", "cc");
}

} //namespace xv6pp::x86
