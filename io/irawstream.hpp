#ifndef XV6PP_IO_IRAWSTREAM_HPP
#define XV6PP_IO_IRAWSTREAM_HPP

#include "rawbuf.hpp"
#include "../libcpp/istream.hpp"

namespace xv6pp::io
{

template<
    typename CharT, 
    typename Traits = std::char_traits<CharT>,
    typename Allocator = std::allocator<char>,
    bool NEVER_SET_GCOUNT = false,
    bool NEVER_CHECK_IOSTATE = false,
    bool CRTP = false,
    bool CRTP_BUF = false>
class basic_irawstream :
    public std::basic_istream<
            CharT, Traits,
            NEVER_SET_GCOUNT, 
            NEVER_CHECK_IOSTATE,
            std::conditional_t<
                CRTP,
                basic_irawstream<
                    CharT, Traits,
                    Allocator,
                    NEVER_SET_GCOUNT,
                    NEVER_CHECK_IOSTATE,
                    CRTP,
                    CRTP_BUF>,
                void>,
            basic_rawbuf<CharT, Traits, Allocator, CRTP_BUF>>
{
    using base = 
        std::basic_istream<
            CharT, Traits,
            NEVER_SET_GCOUNT, 
            NEVER_CHECK_IOSTATE,
            std::conditional_t<
                CRTP,
                basic_irawstream<
                    CharT, Traits,
                    Allocator,
                    NEVER_SET_GCOUNT,
                    NEVER_CHECK_IOSTATE,
                    CRTP,
                    CRTP_BUF>,
                void>,
            basic_rawbuf<CharT, Traits, Allocator, CRTP_BUF>>;
    friend base;

    using upos = std::make_unsigned_t<typename Traits::pos_type>;

public:
    using char_type   = CharT;
    using int_type    = typename Traits::int_type;
    using pos_type    = typename Traits::pos_type;
    using off_type    = typename Traits::off_type;
    using traits_type = Traits;

    basic_irawstream()
        : buf(0), base(&buf) {}

    explicit basic_irawstream(upos pos)
        : buf(pos), base(&buf) {}

    basic_irawstream(const basic_irawstream&) = delete;
    basic_irawstream(basic_irawstream&&) = default;

    basic_irawstream& operator=(const basic_irawstream&) = delete;
    basic_irawstream& operator=(basic_irawstream&&) = default;

    void swap(basic_irawstream& rhs)
    {
        std::swap(*this, rhs);
    }

    basic_rawbuf<CharT, Traits, Allocator, CRTP_BUF>* rdbuf() const
    {
        return const_cast<
            basic_rawbuf<CharT, Traits, Allocator, CRTP_BUF>*>(&buf);
    }

    template<typename T> requires std::is_trivial_v<T>
    basic_irawstream& operator>>(T& obj)
    {
        return read(reinterpret_cast<char_type*>(&obj), sizeof(T));
    }

private:
    basic_rawbuf<CharT, Traits, Allocator, CRTP_BUF> buf;
};

} //namespace xv6pp::io

#endif //XV6PP_IO_IRAWSTREAM_HPP
