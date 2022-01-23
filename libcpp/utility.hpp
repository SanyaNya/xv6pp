#ifndef STD_UTILITY_HPP
#define STD_UTILITY_HPP

#include "type_traits_impl/remove_reference.hpp"
#include "type_traits_impl/add_rvalue_reference.hpp"

namespace std
{

template<typename T>
remove_reference_t<T>&& move(T&& t)
{
    return static_cast<remove_reference_t<T>&&>(t);
}

template<typename T>
add_rvalue_reference_t<T> declval() noexcept;

} //namespace std

#endif //STD_UTILITY_HPP
