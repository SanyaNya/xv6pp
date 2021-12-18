#ifndef X86_HPP
#define X86_HPP

#include "../libcpp/type_traits.hpp"
#include "../libcpp/concepts.hpp"
#include "../libcpp/cstddef.hpp"
#include "../libcpp/cstdint.hpp"

namespace x86
{

namespace detail
{

inline void outb(unsigned short port, unsigned char data)
{
  asm volatile("out %0,%1" : : "a" (data), "d" (port));
}

inline unsigned char inb(unsigned short port)
{
  unsigned char data;

  asm volatile("in %1,%0" : "=a" (data) : "d" (port));
  return data;
}

inline void insl(int port, void *addr, int cnt)
{
  asm volatile("cld; rep insl" :
               "=D" (addr), "=c" (cnt) :
               "d" (port), "0" (addr), "1" (cnt) :
               "memory", "cc");
}

} //namespace detail


template<
    std::explicitly_convertible_to<std::uint16_t> E, 
    std::explicitly_convertible_to<std::uint8_t>  T>
inline void outb(E port, T data)
{
    detail::outb(
        static_cast<std::uint16_t>(port), 
        static_cast<std::uint8_t>(data));
}

template<std::explicitly_convertible_to<std::uint16_t> E>
inline std::uint8_t inb(E port)
{
    return detail::inb(static_cast<std::uint16_t>(port));
}

template<std::explicitly_convertible_to<std::uint16_t> E, typename T>
inline void insl(E port, T* dest, std::size_t count)
{
    detail::insl(
        static_cast<std::uint16_t>(port), 
        reinterpret_cast<std::uint8_t*>(dest), 
        count);
}

template<std::explicitly_convertible_to<std::uint16_t> E>
inline void in_skip(E port, std::size_t count)
{
    for(std::size_t i = 0; i != count; ++i)
        inb(port);
}

} //namespace x86

#endif //X86_HPP
