#ifndef STD_TYPE_TRAITS_IMPL_ADD_VOLATILE_HPP
#define STD_TYPE_TRAITS_IMPL_ADD_VOLATILE_HPP

#include "type_identity.hpp"

namespace std
{

template<typename T>
struct add_volatile : type_identity<volatile T> {};

template<typename T>
using add_volatile_t = typename add_volatile<T>::type;

} //namespace std


#endif //STD_TYPE_TRAITS_IMPL_ADD_VOLATILE_HPP
