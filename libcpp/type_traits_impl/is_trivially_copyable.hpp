#ifndef STD_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP
#define STD_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP

#include "bool_constant.hpp"
#include "remove_all_extents.hpp"
#include "detail/constraints.hpp"

namespace std
{

template<typename T> 
    requires detail::complete_or_cv_void<remove_all_extents_t<T>>
struct is_trivially_copyable
    : bool_constant<__is_trivially_copyable(T)> {};

template<typename T>
    requires detail::complete_or_cv_void<remove_all_extents_t<T>>
constexpr bool is_trivially_copyable_v =
    is_trivially_copyable<T>::value;

} //namespace std

#endif //STD_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP
