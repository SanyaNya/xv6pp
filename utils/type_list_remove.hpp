#ifndef META_TYPE_LIST_REMOVE_HPP
#define META_TYPE_LIST_REMOVE_HPP

#include "type_list.hpp"

namespace meta
{

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

template<typename List, auto P>
using type_list_remove_if_t = 
    typename type_list_remove_if<List, P>::type;


template<typename List, typename T>
struct type_list_remove :
    std::type_identity<
        type_list_remove_if_t<
            List, 
            []<typename A>(){ return std::is_same_v<A, T>; }>> {};

template<typename List, typename T>
using type_list_remove_t = 
    typename type_list_remove<List, T>::type;

} //namespace meta

#endif //META_TYPE_LIST_REMOVE_HPP
