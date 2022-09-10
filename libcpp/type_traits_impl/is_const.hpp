#pragma once

#include "bool_constant.hpp"

namespace std
{

template<typename T>
struct is_const : false_type {};

template<typename T>
struct is_const<const T> : true_type {};

template<typename T>
constexpr bool is_const_v = is_const<T>::value;

} //namespace std
