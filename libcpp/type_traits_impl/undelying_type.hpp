#ifndef STD_TYPE_TRAITS_UNDERLYING_TYPE_HPP
#define STD_TYPE_TRAITS_UNDERLYING_TYPE_HPP

#include "is_enum.hpp"
#include "type_identity.hpp"

namespace std
{

template<typename E> requires is_enum_v<E>
struct underlying_type : type_identity<__underlying_type(E)> {};

template<typename E> requires is_enum_v<E>
using underlying_type_t = typename underlying_type<E>::type;

template<typename E> requires is_enum_v<E>
constexpr auto to_underlying(E e) noexcept
{
    return static_cast<underlying_type_t<E>>(e);
}

} //namespace std

#endif //STD_TYPE_TRAITS_UNDERLYING_TYPE_HPP
