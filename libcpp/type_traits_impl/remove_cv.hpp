#pragma once

#include "remove_const.hpp"
#include "remove_volatile.hpp"

namespace std
{

template<typename T>
struct remove_cv 
    : type_identity<remove_const_t<remove_volatile_t<T>>> {};

template<typename T>
using remove_cv_t = typename remove_cv<T>::type; 

} //namespace std
