#ifndef STD_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_HPP
#define STD_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_HPP

#include "void_t.hpp"
#include "bool_constant.hpp"
#include "../utility.hpp"
#include "detail/constraints.hpp"

namespace std
{

template<detail::complete_or_cv_void_or_unbounded_array T, 
         detail::complete_or_cv_void_or_unbounded_array U, typename  = void>
struct is_nothrow_assignable : false_type {};

template<detail::complete_or_cv_void_or_unbounded_array T,
         detail::complete_or_cv_void_or_unbounded_array U>
struct is_nothrow_assignable<
        T, U, 
        void_t<decltype(noexcept(declval<T>() = declval<U>()))>>
    : true_type{};

template<detail::complete_or_cv_void_or_unbounded_array T,
         detail::complete_or_cv_void_or_unbounded_array U>
inline constexpr bool is_nothrow_assignable_v = 
    is_nothrow_assignable<T, U>::value;

} //namespace std

#endif //STD_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_HPP
