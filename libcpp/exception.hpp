#ifndef STD_EXCEPTION_HPP
#define STD_EXCEPTION_HPP

#include "cstdlib.hpp"

namespace std
{

using terminate_handler = void(*)();

namespace detail
{

inline terminate_handler terminate_func = abort;

} //namespace detail

terminate_handler get_terminate() noexcept
{
    return detail::terminate_func;
}

void set_terminate(terminate_handler f) noexcept
{
    detail::terminate_func = f;
}

[[noreturn]] void terminate() noexcept
{
    detail::terminate_func();
}

} //namespace std

#endif //STD_EXCEPTION_HPP