#ifndef XV6PP_UTILS_EQUAL_INTEGRAL_RANK_HPP
#define XV6PP_UTILS_EQUAL_INTEGRAL_RANK_HPP

#include "../libcpp/type_traits.hpp"
#include "type_list.hpp"

using rank_types = 
    meta::type_list<
        unsigned char, unsigned short, unsigned int, 
        unsigned long, unsigned long long>;

template<typename T>
struct equal_integral_rank
    : std::type_identity<
        rank_types::find_type_if<
            []<typename TArg>(){ return sizeof(T) == sizeof(TArg); }>> {};

template<typename T>
using equal_integral_rank_t = typename equal_integral_rank<T>::type;

#endif //XV6PP_UTILS_EQUAL_INTEGRAL_RANK_HPP
