#include "print.hpp"

namespace xv6pp
{

extern "C" [[noreturn]] void _start()
{
    unsigned int i = 0;
    while(true)
    {
        print(vga_buf+80, "HELLO FROM KERNEL!!!");
        print(vga_buf+160, ++i);
    }
}

} //namespace xv6pp
