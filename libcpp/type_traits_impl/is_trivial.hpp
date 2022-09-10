#pragma once

#include "is_trivially_copyable.hpp"
#include "is_trivially_default_constructible.hpp"
#include "remove_all_extents.hpp"
#include "detail/constraints.hpp"

namespace std
{

template<typename T>
    requires detail::complete_or_cv_void<remove_all_extents_t<T>>
struct is_trivial
    : bool_constant<
        is_trivially_copyable_v<T> && 
        is_trivially_default_constructible_v<T>> {};

template<typename T>
    requires detail::complete_or_cv_void<remove_all_extents_t<T>>
constexpr bool is_trivial_v = is_trivial<T>::value;

} //namespace std
