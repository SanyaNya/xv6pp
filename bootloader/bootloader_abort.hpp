#pragma once

#include "../libcpp/utility.hpp"

namespace std
{
    [[noreturn]] void abort() noexcept
    {
        //do nothing :)
        std::unreachable();
    }
} //namespace std
