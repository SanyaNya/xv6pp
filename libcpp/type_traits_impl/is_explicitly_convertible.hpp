#ifndef STD_TYPE_TRAITS_IS_EXPLICITLY_CONVERTIBLE_HPP
#define STD_TYPE_TRAITS_IS_EXPLICITLY_CONVERTIBLE_HPP

#include "void_t.hpp"
#include "is_void.hpp"
#include "conjunction.hpp"
#include "bool_constant.hpp"

namespace std
{

template<typename From, typename To, typename = void>
struct is_explicitly_convertible : conjunction<is_void<From>, is_void<To>> {};

template<typename From, typename To>
struct is_explicitly_convertible<
        From, To, 
        void_t<decltype(static_cast<To>(declval<From>()))>> : true_type {};

template<typename From, typename To>
inline constexpr bool is_explicitly_convertible_v = 
    is_explicitly_convertible<From, To>::value;

} //namespace std

#endif //STD_TYPE_TRAITS_IS_EXPLICITLY_CONVERTIBLE_HPP