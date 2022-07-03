#ifndef STD_DETAIL_STD_TYPES_HPP
#define STD_DETAIL_STD_TYPES_HPP

#include "../../utils/type_list.hpp"

namespace std::detail
{

using std_types = 
    meta::type_list<
        float,
        double,
        long double,
        bool,
        char,
        signed char,
        unsigned char,
        char8_t,
        char16_t,
        char32_t,
        wchar_t,
        short int,
        int,
        long int,
        long long int,
        unsigned short int,
        unsigned int,
        unsigned long int,
        unsigned long long int>;

} //namespace std::detail

#endif //STD_DETAIL_STD_TYPES_HPP
