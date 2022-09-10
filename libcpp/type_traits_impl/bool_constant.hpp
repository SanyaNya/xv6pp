#pragma once

#include "integral_constant.hpp"

namespace std
{

template<bool B>
using bool_constant = integral_constant<bool, B>;

using false_type = bool_constant<false>;
using true_type  = bool_constant<true>;

} //namespace std
