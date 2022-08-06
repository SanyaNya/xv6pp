#ifndef STD_DETAIL_FUNDAMENTAL_TYPES_HPP
#define STD_DETAIL_FUNDAMENTAL_TYPES_HPP

#include "../../utils/type_list.hpp"

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
    narrow_char_types::append<wide_char_types>;


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

using int_types = signed_int_types::append<unsigned_int_types>;

using floating_point_types =
    meta::type_list<
        float,
        double,
        long double>;


using integral_types = 
    character_types::append<int_types>::push_front<bool>;

using arithmetic_types = 
    floating_point_types::append<integral_types>;

using fundamental_types = 
    arithmetic_types::push_front<void, decltype(nullptr)>;

} //namespace std::detail

#endif //STD_DETAIL_FUNDAMENTAL_TYPES_HPP
