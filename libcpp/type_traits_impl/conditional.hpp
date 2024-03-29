#pragma once

#include "type_identity.hpp"

namespace std
{

template<bool B, typename TTrue, typename TFalse>
struct conditional : type_identity<TTrue> {};

template<typename TTrue, typename TFalse>
struct conditional<false, TTrue, TFalse> : type_identity<TFalse> {};

template<bool B, typename TTrue, typename TFalse>
using conditional_t = typename conditional<B, TTrue, TFalse>::type;

} //namespace std
