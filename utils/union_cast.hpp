#ifndef XV6PP_UTILS_UNION_CAST_HPP
#define XV6PP_UTILS_UNION_CAST_HPP

namespace xv6pp
{

template<typename To, typename From>
    requires (sizeof(From) == sizeof(To))
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
