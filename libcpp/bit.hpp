#ifndef STD_BIT_HPP
#define STD_BIT_HPP

#include "type_traits_impl/is_trivially_copyable.hpp"

namespace std
{

template<typename To, typename From>
    requires (sizeof(From) == sizeof(To)    &&
              is_trivially_copyable_v<From> &&
              is_trivially_copyable_v<To>)
constexpr To bit_cast(const From& from) noexcept
{
    return __builtin_bit_cast(To, from);
}

} //namespace std

#endif //STD_BIT_HPP
