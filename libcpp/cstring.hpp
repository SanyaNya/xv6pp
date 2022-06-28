#ifndef STD_CSTRING_HPP
#define STD_CSTRING_HPP

#include "cstddef_impl/types.hpp"

namespace std
{

void* memcpy(void* dest, const void* src, std::size_t count)
{
    return __builtin_memcpy(dest, src, count);
}

} //namespace std

#endif //STD_LIBCPP_CSTRING_HPP
