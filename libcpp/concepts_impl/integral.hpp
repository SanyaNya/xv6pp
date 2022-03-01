#ifndef STD_CONCEPTS_IMPL_INTEGRAL_HPP
#define STD_CONCEPTS_IMPL_INTEGRAL_HPP

#include "../type_traits_impl/is_integral.hpp"

namespace std
{

template<typename T>
concept integral = is_integral_v<T>;

} //namespace std

#endif //STD_CONCEPTS_IMPL_INTEGRAL_HPP
