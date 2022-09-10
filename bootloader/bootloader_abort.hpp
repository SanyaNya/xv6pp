#pragma once

#include <utility>

namespace std
{
    [[noreturn]] void abort() noexcept
    {
        //do nothing :)
        std::unreachable();
    }
} //namespace std
