#ifndef XV6PP_X86_GDT_HPP
#define XV6PP_X86_GDT_HPP

#include "../libcpp/array.hpp"
#include "SegmentDescriptor.hpp"

namespace xv6pp::x86
{

template<std::size_t N>
struct GDT : std::array<std::uint64_t, N>
{
    template<Segment::IsDescriptor ... Ts>
    constexpr GDT(Ts&& ... ds) noexcept :
        std::array<std::uint64_t, N>
        {
            0, static_cast<std::uint64_t>(ds)...
        } {}

    constexpr auto selector_offset(std::size_t i) const noexcept
    {
        return (*this)[i] - (*this)[0];
    }
};

template<typename ... Ts>
GDT(Ts&& ... ds) -> GDT<sizeof...(ds) + 1>;

#pragma pack(1)
template<std::size_t N>
struct GDT_Description
{
    std::uint16_t size;
    const GDT<N>* gdt;

    constexpr GDT_Description(const GDT<N>& t) noexcept :
        size(sizeof(GDT<N>)), gdt(&t) {}
};

static_assert(
    sizeof(GDT_Description<0>) == 
    (sizeof(std::uint16_t) + sizeof(const GDT<0>*)), 
    "GDT_Description is not packed");

template<std::size_t N>
GDT_Description(const GDT<N>&) -> GDT_Description<N>;

} //namespace xv6pp::x86

#endif //XV6PP_X86_GDT_HPP
