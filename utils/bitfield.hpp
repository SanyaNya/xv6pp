#pragma once

#include "../libcpp/bit.hpp"

namespace xv6pp
{

template<typename TImpl, typename TAlias>
struct bitfield
{
    constexpr bitfield() noexcept = default;
    constexpr bitfield(TAlias t) noexcept
    {
        static_assert(sizeof(TImpl) == sizeof(TAlias));
        *static_cast<TImpl*>(this) = std::bit_cast<TImpl>(t); 
    }

    constexpr TImpl& operator=(TAlias t) noexcept
    {
        static_assert(sizeof(TImpl) == sizeof(TAlias));
        return *static_cast<TImpl*>(this) = std::bit_cast<TImpl>(t);
    }

    constexpr operator TAlias() const noexcept
    {
        static_assert(sizeof(TImpl) == sizeof(TAlias));
        return std::bit_cast<TAlias>(*static_cast<const TImpl*>(this)); 
    }
};

} //namespace xv6pp
