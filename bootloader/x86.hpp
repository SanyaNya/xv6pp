#ifndef X86_HPP
#define X86_HPP

namespace x86
{

extern "C"
{
    void outb(unsigned short port, unsigned char data);
    unsigned char inb(unsigned short port);
    void insd(unsigned short port, unsigned char* dest, unsigned int count);
    void insd_skip(unsigned short port, unsigned int count);
}

} //namespace x86

#endif //X86_HPP
