#pragma once

#include "../type_traits_impl/is_explicitly_convertible.hpp"

namespace std
{

template<typename From, typename To>
concept explicitly_convertible_to = 
    std::is_explicitly_convertible_v<From, To>;

} //namespace std
