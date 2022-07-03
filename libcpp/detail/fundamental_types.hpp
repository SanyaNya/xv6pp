#ifndef STD_DETAIL_FUNDAMENTAL_TYPES_HPP
#define STD_DETAIL_FUNDAMENTAL_TYPES_HPP

#include "../../utils/type_list.hpp"
#include "../../utils/type_list_cat.hpp"

namespace std::detail
{

using narrow_char_types =
    meta::type_list<
        char,
        signed char,
        unsigned char,
        char8_t>;

using wide_char_types =
    meta::type_list<
        char16_t,
        char32_t,
        wchar_t>;

using character_types =
    meta::type_list_cat_t<
        narrow_char_types,
        wide_char_types>;


using signed_int_types =
    meta::type_list<
        short int,
        int,
        long int,
        long long int>;

using unsigned_int_types =
    meta::type_list<
        unsigned short int,
        unsigned int,
        unsigned long int,
        unsigned long long int>;

using int_types =
    meta::type_list_cat_t<
        signed_int_types,
        unsigned_int_types>;


using floating_point_types =
    meta::type_list<
        float,
        double,
        long double>;


using integral_types =
    meta::type_list_cat_t<
        meta::type_list<bool>,
        character_types,
        int_types>;

using arithmetic_types =
    meta::type_list_cat_t<
        floating_point_types,
        integral_types>;

using fundamental_types_except_void =
    meta::type_list_cat_t<
        meta::type_list<decltype(nullptr)>,
        arithmetic_types>;

using fundamental_types =
    meta::type_list_cat_t<
        meta::type_list<void>,
        fundamental_types_except_void>;

} //namespace std::detail

#endif //STD_DETAIL_FUNDAMENTAL_TYPES_HPP
