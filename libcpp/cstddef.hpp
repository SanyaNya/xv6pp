#ifndef STD_CSTDDEF_HPP
#define STD_CSTDDEF_HPP

#include "utility.hpp"

namespace std
{

using size_t = decltype(sizeof(int));
using ptrdiff_t = decltype(declval<int*>()-declval<int*>());
using nullptr_t = decltype(nullptr);
using max_align_t = long double;

} //namespace std

#endif //STD_CSTDDEF_HPP
