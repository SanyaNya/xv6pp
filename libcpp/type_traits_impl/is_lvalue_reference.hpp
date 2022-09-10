#pragma once

#include "bool_constant.hpp"

namespace std
{

template<typename T>
struct is_lvalue_reference : false_type {};

template<typename T>
struct is_lvalue_reference<T&> : true_type {};

template<typename T>
constexpr bool is_lvalue_reference_v = 
    is_lvalue_reference<T>::value;

} //namespace std
