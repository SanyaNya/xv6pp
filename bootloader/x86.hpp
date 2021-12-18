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

extern "C"
{
    void outb(unsigned short port, unsigned char data);
    unsigned char inb(unsigned short port);
    void insd(unsigned short port, unsigned char* dest, unsigned int count);
    void insd_skip(unsigned short port, unsigned int count);
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
inline void insd(E port, T* dest, std::size_t count)
{
    detail::insd(
        static_cast<std::uint16_t>(port), 
        reinterpret_cast<std::uint8_t*>(dest), 
        count);
}

template<std::explicitly_convertible_to<std::uint16_t> E>
inline void insd_skip(E port, std::size_t count)
{
    detail::insd_skip(static_cast<std::uint16_t>(port), count);
}

} //namespace x86

#endif //X86_HPP
