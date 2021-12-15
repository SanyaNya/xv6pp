#ifndef STD_IOS_HPP
#define STD_IOS_HPP

#include "cstdint.hpp"

namespace std
{

class ios_base
{
public:
    using seekdir = std::uint32_t;

    static constexpr seekdir cur = 0;
    static constexpr seekdir beg = 1;
    static constexpr seekdir end = 2;

    //TODO
    //....
};

} //namesapce std

#endif //STD_IOS_HPP
