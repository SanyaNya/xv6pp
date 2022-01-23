#ifndef STD_TYPE_TRAITS_IS_REFERENCE_HPP
#define STD_TYPE_TRAITS_IS_REFERENCE_HPP

#include "bool_constant.hpp"
#include "is_lvalue_reference.hpp"
#include "is_rvalue_reference.hpp"

namespace std
{

template<typename T>
struct is_reference : 
    bool_constant<is_lvalue_reference_v<T> || is_rvalue_reference_v<T>> {};

template<typename T>
inline constexpr bool is_reference_v = is_reference<T>::value;

} //namespace std

#endif //STD_TYPE_TRAITS_IS_REFERENCE_HPP
