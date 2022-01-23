#ifndef STD_TYPE_TRAITS_ADD_LVALUE_REFERENCE_HPP
#define STD_TYPE_TRAITS_ADD_LVALUE_REFERENCE_HPP

#include "type_identity.hpp"
#include "detail/is_referenceable.hpp"

namespace std
{

template<typename T, bool = detail::is_referenceable_v<T>>
struct add_lvalue_reference : type_identity<T> {};

template<typename T>
struct add_lvalue_reference<T, true> : type_identity<T&> {};

template<typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

} //namespace std

#endif //STD_TYPE_TRAITS_ADD_LVALUE_REFERENCE_HPP
