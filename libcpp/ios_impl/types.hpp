#ifndef STD_IOS_IMPL_TYPES_HPP
#define STD_IOS_IMPL_TYPES_HPP

#include "../cstddef.hpp"
#include "../cstdint.hpp"

namespace std
{

using streamoff  = int32_t;
using streamsize = ptrdiff_t;
using mbstate_t  = void; //TODO

template<typename TState>
using fpos = streamoff; //TODO normal impl

using streampos = fpos<mbstate_t>;

} //namesapce std

#endif //STD_IOS_IMPL_TYPES_HPP
