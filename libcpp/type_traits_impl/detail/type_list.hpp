#ifndef STD_TYPE_TRAITS_IMPL_DETAIL_TYPE_LIST_HPP
#define STD_TYPE_TRAITS_IMPL_DETAIL_TYPE_LIST_HPP

#include "../../cstddef.hpp"
#include "../../limits.hpp"
#include "../type_identity.hpp"
#include "../integral_constant.hpp"
#include "../conditional.hpp"
#include "../is_same.hpp"

namespace std::detail
{

struct UNKNOWN_TYPE {};
inline constexpr size_t NOT_FOUND = numeric_limits<size_t>::max();

namespace detail
{

template<typename ... Ts>
struct type_list_helper;

template<typename T, typename ... Ts>
struct type_list_helper<T, Ts...>
{
    template<typename Garbage, size_t I>
    struct get : type_list_helper<Ts...>::template get<Garbage, I-1> {};
    
    //We need to avoid full specialization cause of gcc bug #85282
    template<typename Garbage>
    struct get<Garbage, 0> : type_identity<T> {};

    template<auto P, size_t I, bool = P.template operator()<T>()>
    struct find_if : type_list_helper<Ts...>::template find_if<P, I+1> {};

    template<auto P, size_t I>
    struct find_if<P, I, true> : integral_constant<size_t, I> {};
};

template<>
struct type_list_helper<>
{
    template<size_t I>
    struct get : type_identity<UNKNOWN_TYPE> {};

    template<auto P, size_t I>
    struct find_if : 
        integral_constant<size_t, numeric_limits<size_t>::max()> {};
};

} //namesapce detail


template<typename ... Ts>
struct type_list
{
    template<size_t I>
    using get = 
        typename detail::type_list_helper<Ts...>::template get<void, I>::type;

    template<auto P>
    static constexpr size_t find_if =
        detail::type_list_helper<Ts...>::template find_if<P, 0>::value;

    template<auto P>
    using find_type_if = get<find_if<P>>;

    template<typename T>
    static constexpr size_t find = 
        find_if<[]<typename TArg>(){ return is_same_v<T, TArg>; }>;

    template<typename T>
    using find_type = get<find<T>>;

    template<typename T>
    static constexpr bool exist = 
        find<T> != NOT_FOUND;
};

} //namespace std::detail

#endif //STD_TYPE_TRAITS_IMPL_DETAIL_TYPE_LIST_HPP
