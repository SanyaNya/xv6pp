#pragma once

#include "detail/constraints.hpp"
#include "detail/is_referenceable.hpp"
#include "is_nothrow_constructible.hpp"

namespace std
{

template<detail::complete_or_cv_void_or_unbounded_array T>
    requires detail::is_referenceable_v<T>
struct is_nothrow_move_constructible 
    : is_nothrow_constructible<T, T&&> {};

template<detail::complete_or_cv_void_or_unbounded_array T>
    requires detail::is_referenceable_v<T>
constexpr bool is_nothrow_move_constructible_v = 
    is_nothrow_move_constructible<T>::value;

} //namespace std
