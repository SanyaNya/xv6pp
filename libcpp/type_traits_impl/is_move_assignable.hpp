#ifndef STD_TYPE_TRAITS_IS_MOVE_ASSIGNABLE_HPP
#define STD_TYPE_TRAITS_IS_MOVE_ASSIGNABLE_HPP

#include "bool_constant.hpp"
#include "is_assignable.hpp"
#include "detail/constraints.hpp"
#include "detail/is_referenceable.hpp"

namespace std
{

template<detail::complete_or_cv_void_or_unbounded_array T>
    requires detail::is_referenceable_v<T>
struct is_move_assignable : is_assignable<T, T&&> {};

template<detail::complete_or_cv_void_or_unbounded_array T>
    requires detail::is_referenceable_v<T>
constexpr bool is_move_assignable_v = 
    is_move_assignable<T>::value;

} //namespace std

#endif //STD_TYPE_TRAITS_IS_MOVE_ASSIGNABLE_HPP
