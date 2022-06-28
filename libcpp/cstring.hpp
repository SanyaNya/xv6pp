#ifndef STD_CSTRING_HPP
#define STD_CSTRING_HPP

#include "cstddef_impl/types.hpp"

#define memcpy __builtin_memcpy

namespace std
{

using ::memcpy;

} //namespace std

#endif //STD_LIBCPP_CSTRING_HPP
