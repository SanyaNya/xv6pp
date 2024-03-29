#pragma once

#include "bool_constant.hpp"
#include "is_nothrow_assignable.hpp"
#include "detail/constraints.hpp"
#include "detail/is_referenceable.hpp"

namespace std
{

template<detail::complete_or_cv_void_or_unbounded_array T>
    requires detail::is_referenceable_v<T>
struct is_nothrow_move_assignable : is_nothrow_assignable<T, T&&> {};

template<detail::complete_or_cv_void_or_unbounded_array T>
    requires detail::is_referenceable_v<T>
constexpr bool is_nothrow_move_assignable_v = 
    is_nothrow_move_assignable<T>::value;

} //namespace std
