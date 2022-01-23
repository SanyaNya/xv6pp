#ifndef STD_TYPE_TRAITS_DETAIL_CONSTRAINTS_HPP
#define STD_TYPE_TRAITS_DETAIL_CONSTRAINTS_HPP

#include "../is_void.hpp"

namespace std::detail
{

template<typename T>
concept complete = requires() { sizeof(T); };

template<typename T>
concept cv_void = is_void_v<T>;

template<typename T>
inline constexpr bool is_unbounded_array = false;

template<typename T>
inline constexpr bool is_unbounded_array<T[]> = true;

template<typename T>
concept unbounded_array = is_unbounded_array<T>;

template<typename T>
concept complete_or_cv_void = complete<T> || cv_void<T>;

template<typename T>
concept complete_or_cv_void_or_unbounded_array 
    = complete<T> || cv_void<T> || unbounded_array<T>;

} //namespace

#endif //STD_TYPE_TRAITS_DETAIL_CONSTRAITS_HPP
