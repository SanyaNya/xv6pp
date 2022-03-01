#ifndef XV6PP_UTILS_UNION_CAST_HPP
#define XV6PP_UTILS_UNION_CAST_HPP

#include "../libcpp/type_traits.hpp"

namespace xv6pp
{

template<typename To, typename From>
    requires (sizeof(From) == sizeof(To)      &&
              std::is_standard_layout_v<From> &&
              std::is_standard_layout_v<To>   &&
              std::is_layout_compatible_v<From, To>)
To union_cast(From from)
{
    union
    {
        From f;
        To t;
    } u;

    u.f = from;

    return u.t;
}

} //namespace xv6pp

#endif //XV6PP_UTILS_UNION_CAST_HPP
