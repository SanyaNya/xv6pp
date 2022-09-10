#pragma once

#include "bool_constant.hpp"

namespace std
{

template<typename T>
struct is_enum : bool_constant<__is_enum(T)> {};

template<typename T>
constexpr bool is_enum_v = is_enum<T>::value;

} //namespace std
