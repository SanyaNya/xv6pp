#pragma once

#include "bool_constant.hpp"

namespace std
{

template<typename T1, typename T2>
struct is_same : false_type {};

template<typename T>
struct is_same<T, T> : true_type {};

template<typename T1, typename T2>
constexpr bool is_same_v = is_same<T1, T2>::value;

} //namespace std
