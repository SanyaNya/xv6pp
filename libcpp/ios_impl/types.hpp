#pragma once

#include "../cstddef_impl/types.hpp"
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
