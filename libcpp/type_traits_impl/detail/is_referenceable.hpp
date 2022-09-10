#pragma once

#include "../bool_constant.hpp"
#include "../void_t.hpp"

namespace std::detail
{

template<typename T, typename = void>
struct is_referenceable : false_type {};

template<typename T>
struct is_referenceable<T, void_t<T&>> : true_type {};

template<typename T>
constexpr bool is_referenceable_v = is_referenceable<T>::value;

} //namespace std::detail
