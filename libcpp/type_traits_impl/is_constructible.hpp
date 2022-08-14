#ifndef STD_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP
#define STD_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP

#include "void_t.hpp"
#include "bool_constant.hpp"
#include "../utility_impl/declval.hpp"
#include "detail/constraints.hpp"

namespace std
{

namespace detail
{

template<typename, typename T, typename ... TArgs>
struct is_constructible_helper : std::false_type {};

template<typename T, typename ... TArgs>
struct is_constructible_helper<
        std::void_t<decltype(new T(std::declval<TArgs>()...))>, 
        T, TArgs...> : std::true_type {};

} //namespace detail

template<detail::complete_or_cv_void_or_unbounded_array T, 
         detail::complete_or_cv_void_or_unbounded_array ... TArgs>
struct is_constructible 
    : detail::is_constructible_helper<void, T, TArgs...> {};

template<detail::complete_or_cv_void_or_unbounded_array T, 
         detail::complete_or_cv_void_or_unbounded_array ... TArgs>
constexpr bool is_constructible_v = 
    is_constructible<T, TArgs...>::value;

} //namespace std

#endif //STD_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP
