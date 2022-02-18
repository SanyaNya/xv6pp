#ifndef XV6PP_UTILS_BITFIELD_HPP
#define XV6PP_UTILS_BITFIELD_HPP

#include "union_cast.hpp"

namespace xv6pp
{

template<typename TImpl, typename TAlias>
struct bitfield
{
    bitfield() = default;
    bitfield(TAlias t) { *static_cast<TImpl*>(this) = union_cast<TImpl>(t); }

    TImpl& operator=(TAlias t)
    {
        return *static_cast<TImpl*>(this) = union_cast<TImpl>(t);
    }

    operator TAlias() const { return union_cast<TAlias>(*this); }
};

} //namespace xv6pp

#endif //XV6PP_UTILS_BITFIELD_HPP
