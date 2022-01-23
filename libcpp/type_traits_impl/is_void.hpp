#ifndef STD_TYPE_TRAITS_IS_VOID_HPP
#define STD_TYPE_TRAITS_IS_VOID_HPP

#include "remove_cv.hpp"
#include "bool_constant.hpp"

namespace std
{

template<typename T, typename = remove_cv_t<T>>
struct is_void : false_type {};

template<typename T>
struct is_void<T, void> : true_type {};

template<typename T>
inline constexpr bool is_void_v = is_void<T>::value;

} //namespace std

#endif //STD_TYPE_TRAITS_IS_VOID_HPP
