#ifndef XV6PP_UTILS_BITFIELD_PART_HPP
#define XV6PP_UTILS_BITFIELD_PART_HPP

#include "../../libcpp/cstddef.hpp"
#include "../../libcpp/type_traits.hpp"

namespace xv6pp
{

struct Part
{
    std::size_t begin, end;

    constexpr std::size_t size() const noexcept
    {
        return end - begin;
    }
};

static constexpr std::size_t flat_offset(std::size_t index, const Part parts[]) noexcept
{
    std::size_t off = 0;
    for(std::size_t i = 0; i != index; ++i) off += parts[i].size();

    return off;
}

} //namespace xv6pp

#endif //XV6PP_UTILS_BITFIELD_PART_HPP
