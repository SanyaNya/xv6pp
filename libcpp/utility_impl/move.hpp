#ifndef STD_UTILITY_IMPL_MOVE_HPP
#define STD_UTILITY_IMPL_MOVE_HPP

#include "../type_traits_impl/remove_reference.hpp"

namespace std
{

template<typename T>
remove_reference_t<T>&& move(T&& t)
{
    return static_cast<remove_reference_t<T>&&>(t);
}

} //namespace std

#endif //STD_UTILITY_IMPL_MOVE_HPP
