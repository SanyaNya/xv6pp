#ifndef STD_TYPE_TRAITS_IS_ENUM_HPP
#define STD_TYPE_TRAITS_IS_ENUM_HPP

#include "bool_constant.hpp"

namespace std
{

template<typename T>
struct is_enum : bool_constant<__is_enum(T)> {};

template<typename T>
inline constexpr bool is_enum_v = is_enum<T>::value;

} //namespace std

#endif //STD_TYPE_TRAITS_IS_ENUM_HPP
