#pragma once

namespace std
{

[[noreturn]] inline void unreachable()
{
    __builtin_unreachable();
}

} //namespace std
