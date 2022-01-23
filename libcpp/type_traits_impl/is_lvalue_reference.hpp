#ifndef STD_TYPE_TRAITS_IS_LVALUE_REFERENCE_HPP
#define STD_TYPE_TRAITS_IS_LVALUE_REFERENCE_HPP

#include "bool_constant.hpp"

namespace std
{

template<typename T>
struct is_lvalue_reference : false_type {};

template<typename T>
struct is_lvalue_reference<T&> : true_type {};

template<typename T>
inline constexpr bool is_lvalue_reference_v = 
    is_lvalue_reference<T>::value;

} //namespace std

#endif //STD_TYPE_TRAITS_IS_LVALUE_REFERENCE_HPP
