#pragma once

#include "cstddef_impl/types.hpp"

#define memcpy __builtin_memcpy

namespace std
{

using ::memcpy;

} //namespace std
