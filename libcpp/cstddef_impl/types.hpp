#ifndef STD_CSTDDEF_IMPL_TYPES_HPP
#define STD_CSTDDEF_IMPL_TYPES_HPP

#include "../utility_impl/declval.hpp"

namespace std
{

using size_t      = decltype(sizeof(int));
using ptrdiff_t   = decltype(declval<int*>()-declval<int*>());
using nullptr_t   = decltype(nullptr);
using max_align_t = long double;

} //namespace std

#endif //STD_CSTDDEF_IMPL_TYPES_HPP