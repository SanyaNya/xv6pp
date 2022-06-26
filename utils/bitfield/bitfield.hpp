#ifndef XV6PP_UTILS_BITFIELD_HPP
#define XV6PP_UTILS_BITFIELD_HPP

#include "../../libcpp/bit.hpp"

namespace xv6pp
{

template<typename TImpl, typename TAlias>
struct bitfield
{
    constexpr bitfield() = default;
    constexpr bitfield(TAlias t)
    {
        *static_cast<TImpl*>(this) = std::bit_cast<TImpl>(t); 
    }

    constexpr TImpl& operator=(TAlias t)
    {
        return *static_cast<TImpl*>(this) = std::bit_cast<TImpl>(t);
    }

    constexpr operator TAlias() const
    {
        return std::bit_cast<TAlias>(*static_cast<const TImpl*>(this)); 
    }
};

} //namespace xv6pp

#endif //XV6PP_UTILS_BITFIELD_HPP
