#ifndef STD_CONCEPTS_HPP
#define STD_CONCEPTS_HPP

#include "type_traits.hpp"

namespace std
{

template<typename From, typename To>
concept explicitly_convertible_to = std::is_explicitly_convertible_v<From, To>;

} //namespace std

#endif //STD_CONCEPTS_HPP
