#pragma once

#include "remove_cv.hpp"
#include "bool_constant.hpp"

namespace std
{

template<typename T, typename = remove_cv_t<T>>
struct is_void : false_type {};

template<typename T>
struct is_void<T, void> : true_type {};

template<typename T>
constexpr bool is_void_v = is_void<T>::value;

} //namespace std
