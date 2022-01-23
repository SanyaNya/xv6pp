#ifndef STD_TYPE_TRAITS_BOOL_CONSTANT_HPP
#define STD_TYPE_TRAITS_BOOL_CONSTANT_HPP

#include "integral_constant.hpp"

namespace std
{

template<bool B>
using bool_constant = integral_constant<bool, B>;

using false_type = bool_constant<false>;
using true_type  = bool_constant<true>;

} //namespace std

#endif //STD_TYPE_TRAITS_BOOL_CONSTANT_HPP
