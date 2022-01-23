#ifndef STD_TYPE_TRAITS_REMOVE_CONST_HPP
#define STD_TYPE_TRAITS_REMOVE_CONST_HPP

#include "type_identity.hpp"

namespace std
{

template<typename T>
struct remove_const : type_identity<T> {};

template<typename T>
struct remove_const<const T> : type_identity<T> {};

template<typename T>
using remove_const_t = typename remove_const<T>::type;

} //namespace std

#endif //STD_TYPE_TRAITS_REMOVE_CONST_HPP
