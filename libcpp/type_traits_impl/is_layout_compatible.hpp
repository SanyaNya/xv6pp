#pragma once

#include "detail/constraints.hpp"
#include "bool_constant.hpp"

namespace std
{

template<
    detail::complete_or_cv_void_or_unbounded_array T,
    detail::complete_or_cv_void_or_unbounded_array U>
struct is_layout_compatible
    //: bool_constant<__is_layout_compatible(T, U)> {};
    //TODO when builtin will be implemented
    : bool_constant<true> {};

template<
    detail::complete_or_cv_void_or_unbounded_array T,
    detail::complete_or_cv_void_or_unbounded_array U>
constexpr bool is_layout_compatible_v = is_layout_compatible<T, U>::value;

} //namespace std
