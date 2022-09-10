#pragma once

#include "detail/constraints.hpp"
#include "remove_all_extents.hpp"
#include "bool_constant.hpp"

namespace std
{

template<typename T>
    requires detail::complete_or_cv_void<remove_all_extents_t<T>>
struct is_standard_layout
    : bool_constant<__is_standard_layout(T)> {};

template<typename T>
    requires detail::complete_or_cv_void<remove_all_extents_t<T>>
constexpr bool is_standard_layout_v = is_standard_layout<T>::value;

} //namespace std
