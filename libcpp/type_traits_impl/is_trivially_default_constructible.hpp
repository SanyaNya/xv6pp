#pragma once

#include "is_trivially_constructible.hpp"
#include "detail/constraints.hpp"

namespace std
{

template<detail::complete_or_cv_void_or_unbounded_array T>
struct is_trivially_default_constructible
    : bool_constant<is_trivially_constructible_v<T>> {};

template<detail::complete_or_cv_void_or_unbounded_array T>
constexpr bool is_trivially_default_constructible_v =
    is_trivially_default_constructible<T>::value;

} //namespace std
