#pragma once

#include "../utility_impl/declval.hpp"
#include "../../meta/fundamental_types.hpp"

namespace std
{

using size_t      = decltype(sizeof(int));
using ptrdiff_t   = decltype(declval<int*>()-declval<int*>());
using nullptr_t   = decltype(nullptr);

using max_align_t =
    meta::fundamental_types::
        remove<void>::
            max<[]<typename A, typename B>(){ return (alignof(A) > alignof(B)); }>;

} //namespace std
