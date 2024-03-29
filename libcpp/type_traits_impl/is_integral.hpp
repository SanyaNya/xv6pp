#pragma once

#include "bool_constant.hpp"
#include "remove_cv.hpp"
#include "../../meta/type_list.hpp"

namespace std
{

template<typename T>
struct is_integral : 
    bool_constant<
        meta::type_list<
            bool, 
            char,
            signed char,
            unsigned char,
            wchar_t,
            char8_t,
            char16_t,
            char32_t,
            short,
            unsigned short,
            int,
            unsigned int,
            long,
            unsigned long,
            long long,
            unsigned long long>::exist<T>> {};

template<typename T>
constexpr bool is_integral_v = is_integral<remove_cv_t<T>>::value;

} //namespace std
