#pragma once

#include "bool_constant.hpp"
#include "detail/constraints.hpp"

namespace std
{

template<detail::complete_or_cv_void_or_unbounded_array T, 
         detail::complete_or_cv_void_or_unbounded_array ... TArgs>
struct is_trivially_constructible
    : bool_constant<__is_trivially_constructible(T, TArgs...)> {};

template<detail::complete_or_cv_void_or_unbounded_array T,
         detail::complete_or_cv_void_or_unbounded_array ... TArgs>
constexpr bool is_trivially_constructible_v = 
    is_trivially_constructible<T, TArgs...>::value;

} //namespace std
