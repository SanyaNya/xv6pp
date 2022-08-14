#ifndef STD_TYPE_TRAITS_IS_FUNCTION_HPP
#define STD_TYPE_TRAITS_IS_FUNCTION_HPP

#include "bool_constant.hpp"
#include "is_const.hpp"
#include "is_reference.hpp"

namespace std
{

template<typename T>
struct is_function
    : bool_constant<!is_const_v<const T> && !is_reference_v<T>> {};

template<typename T>
constexpr bool is_function_v = is_function<T>::value;

} //namespace std

#endif //STD_TYPE_TRAITS_IS_FUNCTION_HPP
