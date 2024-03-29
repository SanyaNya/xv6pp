#pragma once

#include "bool_constant.hpp"
#include "remove_cv.hpp"

namespace std
{

template<typename T, typename TR = remove_cv_t<T>>
struct is_bool : bool_constant<false> {};

template<typename T>
struct is_bool<T, bool> : bool_constant<true> {};

template<typename T>
constexpr bool is_bool_v = is_bool<T>::value;

} //namespace std
