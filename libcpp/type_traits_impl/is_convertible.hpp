#ifndef STD_TYPE_TRAITS_IS_CONVERTIBLE_HPP
#define STD_TYPE_TRAITS_IS_CONVERTIBLE_HPP

#include "detail/constraints.hpp"
#include "bool_constant.hpp"
#include "void_t.hpp"
#include "../utility_impl/declval.hpp"

namespace std
{

namespace detail
{

template<typename To>
inline To test_convert(To);

} //namespace detail

template<detail::complete_or_cv_void_or_unbounded_array From,
         detail::complete_or_cv_void_or_unbounded_array To,
         typename = void>
struct is_convertible : false_type {};

template<detail::complete_or_cv_void_or_unbounded_array From,
         detail::complete_or_cv_void_or_unbounded_array To>
struct is_convertible<
        From, To, 
        void_t<decltype(detail::test_convert(declval<From>()))>> 
    : true_type {};

template<detail::complete_or_cv_void_or_unbounded_array From,
         detail::complete_or_cv_void_or_unbounded_array To>
inline constexpr bool is_convertible_v = is_convertible<From, To>::value;

} //namespace std

#endif //STD_TYPE_TRAITS_IS_CONVERTIBLE_HPP
