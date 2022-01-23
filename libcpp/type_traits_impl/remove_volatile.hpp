#ifndef STD_TYPE_TRAITS_REMOVE_VOLATILE_HPP
#define STD_TYPE_TRAITS_REMOVE_VOLATILE_HPP

#include "type_identity.hpp"

namespace std
{

template<typename T>
struct remove_volatile : type_identity<T> {};

template<typename T>
struct remove_volatile<volatile T> : type_identity<T> {};

template<typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

} //namespace std

#endif //STD_TYPE_TRAITS_REMOVE_VOLATILE_HPP
