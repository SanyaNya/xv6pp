#pragma once

#include "type_identity.hpp"

namespace std
{

template<typename T>
struct add_const : type_identity<const T> {};

template<typename T>
using add_const_t = typename add_const<T>::type;

} //namespace std
