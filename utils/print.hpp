#ifndef XV6PP_PRINT_HPP
#define XV6PP_PRINT_HPP

namespace xv6pp
{

inline short* const vga_buf = reinterpret_cast<short*>(0xb8000);
inline constexpr short color = 0x0200;

inline void print(short* buf, const char* str)
{
    while(*str != 0) *buf++ = color | *str++;
}

inline void print(short* buf, unsigned int i)
{
   *buf++ = color | '0';
   *buf++ = color | 'x';
    for(short* e = buf+7; e != buf-1; i >>= 4, --e)
        *e = color | (i%16 + (i%16 > 9 ? 97-10 : 48));
}

} //namesapce xv6pp

#endif //XV6PP_PRINT_HPP