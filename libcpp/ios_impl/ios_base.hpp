#pragma once

#include "../type_traits_impl/underlying_type.hpp"
#include "../type_traits_impl/is_same.hpp"

namespace std
{

namespace detail
{

template<bool B>
class ios_base_enable_virtual {};

template<>
class ios_base_enable_virtual<true>
{
public:
    virtual ~ios_base_enable_virtual() = default;        
};

} //namespace detail

template<typename TImpl = void>
class ios_base_crtp : 
    public detail::ios_base_enable_virtual<is_same_v<TImpl, void>>
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

    //callbacks
    //TODO

protected:
    ios_base_crtp() = default;
};

using ios_base = ios_base_crtp<>;

constexpr ios_base::iostate operator&(
        ios_base::iostate lhs, ios_base::iostate rhs)
{
    return static_cast<ios_base::iostate>(
            to_underlying(lhs) & to_underlying(rhs));
}

constexpr ios_base::openmode operator&(
        ios_base::openmode lhs, ios_base::openmode rhs)
{
    return static_cast<ios_base::openmode>(
            to_underlying(lhs) & to_underlying(rhs));
}

constexpr ios_base::seekdir operator&(
        ios_base::seekdir lhs, ios_base::seekdir rhs)
{
    return static_cast<ios_base::seekdir>(
            to_underlying(lhs) & to_underlying(rhs));
}


constexpr ios_base::iostate operator|(
        ios_base::iostate lhs, ios_base::iostate rhs)
{
    return static_cast<ios_base::iostate>(
            to_underlying(lhs) | to_underlying(rhs));
}

constexpr ios_base::openmode operator|(
        ios_base::openmode lhs, ios_base::openmode rhs)
{
    return static_cast<ios_base::openmode>(
            to_underlying(lhs) | to_underlying(rhs));
}

constexpr ios_base::seekdir operator|(
        ios_base::seekdir lhs, ios_base::seekdir rhs)
{
    return static_cast<ios_base::seekdir>(
            to_underlying(lhs) | to_underlying(rhs));
}


constexpr ios_base::iostate operator~(ios_base::iostate state)
{
    return static_cast<ios_base::iostate>(to_underlying(state));
}

constexpr ios_base::openmode operator~(ios_base::openmode state)
{
    return static_cast<ios_base::openmode>(to_underlying(state));
}

constexpr ios_base::seekdir operator~(ios_base::seekdir state)
{
    return static_cast<ios_base::seekdir>(to_underlying(state));
}

} //namespace std
