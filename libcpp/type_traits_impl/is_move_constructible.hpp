#pragma once

#include "detail/constraints.hpp"
#include "detail/is_referenceable.hpp"
#include "is_constructible.hpp"

namespace std
{

template<detail::complete_or_cv_void_or_unbounded_array T>
    requires detail::is_referenceable_v<T>
struct is_move_constructible 
    : is_constructible<T, T&&> {};

template<detail::complete_or_cv_void_or_unbounded_array T>
    requires detail::is_referenceable_v<T>
constexpr bool is_move_constructible_v = 
    is_move_constructible<T>::value;

} //namespace std
