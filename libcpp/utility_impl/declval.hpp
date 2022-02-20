#ifndef STD_UTILITY_IMPL_DECLVAL_HPP
#define STD_UTILITY_IMPL_DECLVAL_HPP

#include "../type_traits_impl/add_rvalue_reference.hpp"

namespace std
{

template<typename T>
add_rvalue_reference_t<T> declval() noexcept;

} //namespace std

#endif //STD_UTILITY_IMPL_DECLVAL_HPP
