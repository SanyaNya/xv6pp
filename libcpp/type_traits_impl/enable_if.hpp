#ifndef STD_TYPE_TRAITS_IMPL_ENABLE_IF_HPP
#define STD_TYPE_TRAITS_IMPL_ENABLE_IF_HPP

#include "type_identity.hpp"

namespace std
{

template<bool, typename = void>
struct enable_if {};

template<typename T>
struct enable_if<true, T> : type_identity<T> {};

template<bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;

} //namespace std

#endif //STD_TYPE_TRAITS_IMPL_ENABLE_IF_HPP
