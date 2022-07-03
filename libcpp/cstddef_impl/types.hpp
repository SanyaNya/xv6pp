#ifndef STD_CSTDDEF_IMPL_TYPES_HPP
#define STD_CSTDDEF_IMPL_TYPES_HPP

#include "../utility_impl/declval.hpp"
#include "../../utils/type_list.hpp"

namespace std
{

using size_t      = decltype(sizeof(int));
using ptrdiff_t   = decltype(declval<int*>()-declval<int*>());
using nullptr_t   = decltype(nullptr);

namespace detail
{

using std_types = 
    meta::type_list<
        nullptr_t,
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

} //namespace detail


using max_align_t = 
    typename detail::std_types::template max<
        []<typename A, typename B>(){ return (alignof(A) > alignof(B)); }>;

} //namespace std

#endif //STD_CSTDDEF_IMPL_TYPES_HPP
