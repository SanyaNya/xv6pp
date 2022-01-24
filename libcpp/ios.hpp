#ifndef STD_IOS_HPP
#define STD_IOS_HPP

#include "cstdint.hpp"
#include "cstddef.hpp"
#include "type_traits_impl/underlying_type.hpp"

namespace std
{

using streamoff  = int64_t;
using streamsize = ptrdiff_t;
using mbstate_t  = void; //TODO

template<typename TState>
using fpos = streamoff; //TODO normal impl

using streampos = fpos<mbstate_t>;

class ios_base
{
public:
    //TODO
    //class failure

    //fmtflags
    //TODO

    //iostate
    enum class iostate
    {
        badbit  = 1 << 0,
        eofbit  = 1 << 1,
        failbit = 1 << 2,
        goodbit = 1 << 3
    };

    static constexpr iostate badbit  = iostate::badbit;
    static constexpr iostate eofbit  = iostate::eofbit;
    static constexpr iostate failbit = iostate::failbit;
    static constexpr iostate goodbit = iostate::goodbit;

    //openmode
    enum class openmode
    {
        app    = 1 << 0,
        ate    = 1 << 1,
        binary = 1 << 2,
        in     = 1 << 3,
        out    = 1 << 4,
        trunc  = 1 << 5
    };

    static constexpr openmode app    = openmode::app;
    static constexpr openmode ate    = openmode::ate;
    static constexpr openmode binary = openmode::binary;
    static constexpr openmode in     = openmode::in;
    static constexpr openmode out    = openmode::out;
    static constexpr openmode trunc  = openmode::trunc;

    //seekdir
    enum class seekdir
    {
        cur,
        beg,
        end
    };

    static constexpr seekdir cur = seekdir::cur;
    static constexpr seekdir beg = seekdir::beg;
    static constexpr seekdir end = seekdir::end;

    //class Init;
    //TODO

    //fmtflags state
    //TODO
    
    //locales
    //TODO

    //storage
    //TODO

    //destructor
    virtual ~ios_base() = default;

    //callbacks
    //TODO

protected:
    ios_base() = default;
};

inline constexpr ios_base::iostate operator|(
        ios_base::iostate lhs, ios_base::iostate rhs)
{
    return static_cast<ios_base::iostate>(
            to_underlying(lhs) | to_underlying(rhs));
}

inline constexpr ios_base::openmode operator|(
        ios_base::openmode lhs, ios_base::openmode rhs)
{
    return static_cast<ios_base::openmode>(
            to_underlying(lhs) | to_underlying(rhs));
}

inline constexpr ios_base::seekdir operator|(
        ios_base::seekdir lhs, ios_base::seekdir rhs)
{
    return static_cast<ios_base::seekdir>(
            to_underlying(lhs) | to_underlying(rhs));
}

} //namesapce std

#endif //STD_IOS_HPP
