#pragma once

#include "../type_traits_impl/is_integral.hpp"

namespace std
{

template<typename T>
concept integral = is_integral_v<T>;

} //namespace std
