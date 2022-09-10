#pragma once

#include "../type_traits_impl/add_rvalue_reference.hpp"

namespace std
{

template<typename T>
add_rvalue_reference_t<T> declval() noexcept;

} //namespace std
