#pragma once

#include "../cstddef_impl/types.hpp"
#include "type_identity.hpp"

namespace std
{

template<typename T>
struct remove_extent : type_identity<T> {};

template<typename T>
struct remove_extent<T[]> : type_identity<T> {};

template<typename T, size_t N>
struct remove_extent<T[N]> : type_identity<T> {};

} //namespace std
