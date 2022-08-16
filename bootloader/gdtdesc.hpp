#ifndef XV6PP_BOOTLOADER_GDTDESC_HPP
#define XV6PP_BOOTLOADER_GDTDESC_HPP

#include "../x86/gdt.hpp"

constexpr xv6pp::x86::GDT gdt
{
    xv6pp::x86::Segment::Descriptor<xv6pp::x86::Segment::Type::Code>
    {
        0x0, 0xffffffff, 
        xv6pp::x86::Segment::Access<xv6pp::x86::Segment::Type::Code>
        {
            xv6pp::x86::Segment::Readable::Yes,
            xv6pp::x86::Segment::ConformingPrivilege::Equal_Ring,
            xv6pp::x86::Segment::Privilege::Kernel
        },
        xv6pp::x86::Segment::Flags
        {
            xv6pp::x86::Segment::Size::bit32,
            xv6pp::x86::Segment::LimitGranularity::kib4
        }
    },

    xv6pp::x86::Segment::Descriptor<xv6pp::x86::Segment::Type::Data>
    {
        0x0, 0xffffffff,
        xv6pp::x86::Segment::Access<xv6pp::x86::Segment::Type::Data>
        {
            xv6pp::x86::Segment::Writable::Yes,
            xv6pp::x86::Segment::Direction::Up,
            xv6pp::x86::Segment::Privilege::Kernel
        },
        xv6pp::x86::Segment::Flags
        {
            xv6pp::x86::Segment::Size::bit32,
            xv6pp::x86::Segment::LimitGranularity::kib4
        }
    }
};

constinit xv6pp::x86::GDT_Description gdtdesc(gdt);

#endif //XV6PP_BOOTLOADER_GDTDESC_HPP
