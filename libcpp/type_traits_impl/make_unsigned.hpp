#pragma once

#include "type_identity.hpp"
#include "conditional.hpp"
#include "detail/constraints.hpp"
#include "detail/match_cv.hpp"
#include "../../meta/type_list.hpp"

namespace std
{

namespace detail
{

template<typename T>
struct make_unsigned_non_cv_integral : type_identity<T> {};

template<>
struct make_unsigned_non_cv_integral<char> : 
    type_identity<unsigned char> {};

template<>
struct make_unsigned_non_cv_integral<signed char> : 
    type_identity<unsigned char> {};

template<>
struct make_unsigned_non_cv_integral<short> : 
    type_identity<unsigned short> {};

template<>
struct make_unsigned_non_cv_integral<int> : 
    type_identity<unsigned int> {};

template<>
struct make_unsigned_non_cv_integral<long> : 
    type_identity<unsigned long> {};

template<>
struct make_unsigned_non_cv_integral<long long> : 
    type_identity<unsigned long long> {};

using rank_types = meta::type_list<unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long>;

template<typename T>
struct make_unsigned_non_cv_enum
    : type_identity<
        rank_types::find_type_if<
            []<typename TArg>(){ return sizeof(T) <= sizeof(TArg); }>> {};

template<typename T, bool = is_integral_v<T>>
struct make_non_cv_unsigned : 
    make_unsigned_non_cv_enum<remove_cv_t<T>> {};

template<typename T>
struct make_non_cv_unsigned<T, true> : 
    make_unsigned_non_cv_integral<remove_cv_t<T>> {};

template<typename T>
using make_non_cv_unsigned_t = typename make_non_cv_unsigned<T>::type;

} //namespace detail

template<detail::non_bool_integral_or_enum T>
struct make_unsigned : 
    detail::match_cv<T, detail::make_non_cv_unsigned_t<T>> {};

template<detail::non_bool_integral_or_enum T>
using make_unsigned_t = typename make_unsigned<T>::type;

} //namepace std
