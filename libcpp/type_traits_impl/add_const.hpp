#ifndef STD_TYPE_TRAITS_IMPL_ADD_CONST_HPP
#define STD_TYPE_TRAITS_IMPL_ADD_CONST_HPP

#include "type_identity.hpp"

namespace std
{

template<typename T>
struct add_const : type_identity<const T> {};

template<typename T>
using add_const_t = typename add_const<T>::type;

} //namespace std

#endif //STD_TYPE_TRAITS_IMPL_ADD_CONST_HPP
