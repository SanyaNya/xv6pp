#ifndef XV6PP_UTILS_BITFIELD_HPP
#define XV6PP_UTILS_BITFIELD_HPP

#include "../libcpp/bit.hpp"

namespace xv6pp
{

template<typename TImpl, typename TAlias>
struct bitfield
{
    bitfield() = default;
    bitfield(TAlias t)
    {
        static_assert(sizeof(TImpl) == sizeof(TAlias));

        *static_cast<TImpl*>(this) = std::bit_cast<TImpl>(t); 
    }

    TImpl& operator=(TAlias t)
    {
        static_assert(sizeof(TImpl) == sizeof(TAlias));

        return *static_cast<TImpl*>(this) = std::bit_cast<TImpl>(t);
    }

    operator TAlias() const
    {
        static_assert(sizeof(TImpl) == sizeof(TAlias));

        return std::bit_cast<TAlias>(*this); 
    }
};

} //namespace xv6pp

#endif //XV6PP_UTILS_BITFIELD_HPP
