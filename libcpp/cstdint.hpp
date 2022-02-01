#ifndef STD_CSTDINT_HPP
#define STD_CSTDINT_HPP

namespace std
{
    using int8_t   = signed char;
    using int16_t  = short;
    using int32_t  = int;
    using int64_t  = long long;

    using uint8_t  = unsigned char;
    using uint16_t = unsigned short;
    using uint32_t = unsigned int;
    using uint64_t = unsigned long long;

    static_assert(sizeof(int8_t)  == 1);
    static_assert(sizeof(int16_t) == 2);
    static_assert(sizeof(int32_t) == 4);
    static_assert(sizeof(int64_t) == 8);

    static_assert(sizeof(uint8_t)  == 1);
    static_assert(sizeof(uint16_t) == 2);
    static_assert(sizeof(uint32_t) == 4);
    static_assert(sizeof(uint64_t) == 8);
}

#endif //STD_CSTDINT_HPP
