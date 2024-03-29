#pragma once

#include <limits>
#include <type_traits_impl/type_identity.hpp>
#include <type_traits_impl/integral_constant.hpp>
#include <type_traits_impl/conditional.hpp>
#include <type_traits_impl/is_same.hpp>

namespace meta
{

template<typename...>
struct type_list;

using uint = unsigned int;

struct UNKNOWN_TYPE {};
constexpr uint NOT_FOUND = std::numeric_limits<uint>::max();

namespace detail
{

template<auto Less, typename T1, typename T2>
static constexpr bool less_helper()
{
    if constexpr(std::is_same_v<T2, UNKNOWN_TYPE>) return true;
    else return Less.template operator()<T1, T2>();
}

template<auto More, typename T1, typename T2>
static constexpr bool more_helper()
{
    if constexpr(std::is_same_v<T2, UNKNOWN_TYPE>) return true;
    else return More.template operator()<T1, T2>();
}

template<typename ... Ts>
struct type_list_helper;

template<typename T, typename ... Ts>
struct type_list_helper<T, Ts...>
{
    template<typename Garbage, uint I>
    struct get : type_list_helper<Ts...>::template get<Garbage, I-1> {};
    
    //We need to avoid full specialization cause of gcc bug #85282
    template<typename Garbage>
    struct get<Garbage, 0> : std::type_identity<T> {};

    using front = typename get<void, 0>::type;
    using back =  typename get<void, sizeof...(Ts)>::type;

    template<auto P, uint I, bool = P.template operator()<T>()>
    struct find_if : type_list_helper<Ts...>::template find_if<P, I+1> {};

    template<auto P, uint I>
    struct find_if<P, I, true> : std::integral_constant<uint, I> {};

    template<auto Less>
    struct min : 
        std::conditional<
            less_helper<
                Less, 
                T, 
                typename type_list_helper<Ts...>::template min<Less>::type>(),
            T, 
            typename type_list_helper<Ts...>::template min<Less>::type> {};

    template<auto More>
    struct max :
        std::conditional<
            more_helper<
                More,
                T,
                typename type_list_helper<Ts...>::template max<More>::type>(),
            T,
            typename type_list_helper<Ts...>::template max<More>::type> {};
};

template<>
struct type_list_helper<>
{
    template<typename, uint I>
    struct get : std::type_identity<UNKNOWN_TYPE> {};

    using front = UNKNOWN_TYPE;
    using back = UNKNOWN_TYPE;

    template<auto P, uint I>
    struct find_if : 
        std::integral_constant<uint, std::numeric_limits<uint>::max()> {};

    template<auto Less>
    struct min : std::type_identity<UNKNOWN_TYPE> {};

    template<auto More>
    struct max : std::type_identity<UNKNOWN_TYPE> {};
};

template<typename ... Ts>
struct type_list_cat;

template<typename T, typename ... Ts>
struct type_list_cat<T, Ts...> :
    std::type_identity<
        typename type_list_cat<
            T,
            typename type_list_cat<Ts...>::type>::type> {};

template<typename ... Ts1, typename ... Ts2>
struct type_list_cat<
    type_list<Ts1...>, type_list<Ts2...>> :
        std::type_identity<
            type_list<Ts1..., Ts2...>> {};

template<>
struct type_list_cat<> :
    std::type_identity<type_list<>> {};

template<typename List, auto P>
struct type_list_remove_if;

template<typename T, typename ... Ts, auto P>
struct type_list_remove_if<type_list<T, Ts...>, P> :
    std::type_identity<
        std::conditional_t<
            P.template operator()<T>(),
            typename type_list_remove_if<type_list<Ts...>, P>::type,
            typename type_list<T>::template append<
                typename type_list_remove_if<type_list<Ts...>, P>::type>>> {};

template<auto P>
struct type_list_remove_if<type_list<>, P> :
    std::type_identity<type_list<>> {};

} //namesapce detail


template<typename ... Ts>
struct type_list
{
    static constexpr uint size = sizeof...(Ts);

    template<uint I>
    using get = 
        typename detail::type_list_helper<Ts...>::template get<void, I>::type;

    using front = typename detail::type_list_helper<Ts...>::front;
    using back = typename detail::type_list_helper<Ts...>::back;

    template<auto P>
    static constexpr uint find_if =
        detail::type_list_helper<Ts...>::template find_if<P, 0>::value;

    template<auto P>
    using find_type_if = get<find_if<P>>;

    template<typename T>
    static constexpr uint find = 
        find_if<[]<typename TArg>(){ return std::is_same_v<T, TArg>; }>;

    template<typename T>
    using find_type = get<find<T>>;

    template<typename T>
    static constexpr bool exist = 
        find<T> != NOT_FOUND;

    template<auto Less>
    using min =
        typename detail::type_list_helper<Ts...>::template min<Less>::type;

    template<auto More>
    using max =
        typename detail::type_list_helper<Ts...>::template max<More>::type;

    template<typename ... ATs>
    using push_back = type_list<Ts..., ATs...>;

    template<typename ... ATs>
    using push_front = type_list<ATs..., Ts...>;

    template<typename ... TLs>
    using append = typename detail::type_list_cat<type_list<Ts...>, TLs...>::type;

    template<auto P>
    using remove_if = typename detail::type_list_remove_if<type_list<Ts...>, P>::type;

    template<typename T>
    using remove = remove_if<[]<typename A>(){ return std::is_same_v<A, T>; }>;
};

} //namespace meta
