#pragma once

#include "type_identity.hpp"
#include "detail/is_referenceable.hpp"

namespace std
{

template<typename T, bool = detail::is_referenceable_v<T>>
struct add_rvalue_reference : type_identity<T> {};

template<typename T>
struct add_rvalue_reference<T, true> : type_identity<T&&> {};

template<typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

} //namesapce std
