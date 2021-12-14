#ifndef STD_CSTDDEF_HPP
#define STD_CSTDDEF_HPP

namespace std
{

using size_t = unsigned int;
using ptrdiff_t = int;
using nullptr_t = decltype(nullptr);
using max_align_t = long double;

} //namespace std

#endif //STD_CSTDDEF_HPP
