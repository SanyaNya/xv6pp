#ifndef STD_TYPE_TRAITS_REMOVE_ALL_EXTENTS_HPP
#define STD_TYPE_TRAITS_REMOVE_ALL_EXTENTS_HPP

#include "remove_extent.hpp"
#include "type_identity.hpp"
#include "../cstddef.hpp"

namespace std
{

template<typename T>
struct remove_all_extents : type_identity<T> {};

template<typename T>
struct remove_all_extents<T[]> : remove_all_extents<T> {};

template<typename T, std::size_t N>
struct remove_all_extents<T[N]> : remove_all_extents<T> {};

template<typename T>
using remove_all_extents_t = typename remove_all_extents<T>::type;

} //namespace std

#endif //STD_TYPE_TRAITS_REMOVE_ALL_EXTENTS_HPP
