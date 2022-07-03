#ifndef META_TYPE_LIST_CAT_HPP
#define META_TYPE_LIST_CAT_HPP

#include "type_list.hpp"

namespace meta
{

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

template<typename ... Ts>
using type_list_cat_t = typename type_list_cat<Ts...>::type;

} //namespace meta

#endif //META_TYPE_LIST_CAT_HPP
