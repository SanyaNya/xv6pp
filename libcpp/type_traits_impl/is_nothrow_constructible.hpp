#pragma once

#include "void_t.hpp"
#include "bool_constant.hpp"
#include "../utility_impl/declval.hpp"
#include "detail/constraints.hpp"

namespace std
{

namespace detail
{

template<typename, typename T, typename ... TArgs>
struct is_nothrow_constructible_helper : std::false_type {};

template<typename T, typename ... TArgs>
struct is_nothrow_constructible_helper<
        std::void_t<decltype(noexcept(new T(std::declval<TArgs>()...)))>, 
        T, TArgs...> : std::true_type {};

} //namespace detail

template<detail::complete_or_cv_void_or_unbounded_array T, 
         detail::complete_or_cv_void_or_unbounded_array ... TArgs>
struct is_nothrow_constructible 
    : detail::is_nothrow_constructible_helper<void, T, TArgs...> {};

template<detail::complete_or_cv_void_or_unbounded_array T, 
         detail::complete_or_cv_void_or_unbounded_array ... TArgs>
constexpr bool is_nothrow_constructible_v = 
    is_nothrow_constructible<T, TArgs...>::value;

} //namespace std
