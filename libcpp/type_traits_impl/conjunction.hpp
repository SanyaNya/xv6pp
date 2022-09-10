#pragma once

#include "bool_constant.hpp"

namespace std
{

template<typename ... Bs>
struct conjunction : bool_constant<(Bs::value && ...)> {};

template<typename ... Bs>
constexpr bool conjunction_v = conjunction<Bs...>::value;

} //namespace std
