#pragma once

#include "type_identity.hpp"

namespace std
{

template<typename T>
struct remove_reference : type_identity<T> {};

template<typename T>
struct remove_reference<T&> : type_identity<T> {};

template<typename T>
struct remove_reference<T&&> : type_identity<T> {};

template<typename T>
using remove_reference_t = typename remove_reference<T>::type;

} //namespace std
