#include "print.hpp"

namespace xv6pp
{

extern "C" void _start()
{
    for(int x = 3; x < 190; x++)
        print(vga_buf+x*80, "HELLO FROM KERNELQLFKQEFNQL:EFKQ:LEKFN:LQKENF:LQKENF:LQKENF:LQKENF:LQKENF:LQKENF:QLKEFNQ:LEFK!!!");
}

} //namespace xv6pp
