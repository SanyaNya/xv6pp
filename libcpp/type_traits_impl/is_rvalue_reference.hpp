#pragma once

#include "bool_constant.hpp"

namespace std
{

template<typename T>
struct is_rvalue_reference : false_type {};

template<typename T>
struct is_rvalue_reference<T&> : true_type {};

template<typename T>
constexpr bool is_rvalue_reference_v = 
    is_rvalue_reference<T>::value;

} //namespace std
