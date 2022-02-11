#ifndef STD_ISTREAM_HPP
#define STD_ISTREAM_HPP

#include "string_impl/char_traits.hpp"
#include "ios_impl/basic_ios.hpp"

namespace std
{

namespace detail
{

template<bool NEVER_SET_GCOUNT>
struct gcount_storage
{
    constexpr gcount_storage(streamsize count) : get_count(count) {}

    constexpr streamsize get() const { return get_count; }
    constexpr void set(streamsize count) { get_count = count; }

private:
    streamsize get_count;
};

template<>
struct gcount_storage<true>
{
    constexpr gcount_storage(streamsize) {}

    constexpr streamsize get() const { return 0; }
    constexpr void set(streamsize) {}
};

} //namespace detail

template<
    typename CharT, 
    typename Traits = char_traits<CharT>,
    bool NEVER_SET_GCOUNT = false,
    bool NEVER_CHECK_IOSTATE = false,
    typename TImpl = void,
    typename TStreambufImpl = void>
class basic_istream : 
    /*virtual*/ public basic_ios<CharT, Traits, NEVER_CHECK_IOSTATE, TImpl, TStreambufImpl>
{
public:
    //types (inherited from basic_ios)
    using char_type   = typename Traits::char_type;
    using int_type    = typename Traits::int_type;
    using pos_type    = typename Traits::pos_type;
    using off_type    = typename Traits::off_type;
    using traits_type = Traits;

    //constructor/destructor
    basic_istream(basic_streambuf<CharT, Traits, TStreambufImpl>* sb)
        : get_count(0)
    {
        this->init(sb);
    }

    //prefix/suffix
    class sentry
    {
        bool is_ok = false;
    
    public:
        explicit sentry(
                basic_istream<
                    CharT, Traits, 
                    NEVER_SET_GCOUNT, 
                    NEVER_CHECK_IOSTATE, 
                    TImpl, TStreambufImpl>& is, 
                bool /*noskipws*/ = false)
        {
            if(is.good()) is_ok = true;
            else is.setstate(ios_base::failbit);
            //TODO other requirements
        }
        ~sentry() = default;

        explicit operator bool() const { return is_ok; }

        sentry(const sentry&) = delete;
        sentry& operator=(const sentry&) = delete;
    };

    //formatted input
    //TODO

    //unformatted input
    streamsize gcount() const { return get_count.get(); }

    basic_istream& read(char_type* s, streamsize n)
    {
        //TODO exceptions
        get_count.set(0);

        if(sentry(*this, true))
        {
            get_count.set(this->rdbuf()->sgetn(s, n));

            [[unlikely]] if(get_count.get() != n)
                this->setstate(ios_base::eofbit | ios_base::failbit);
        }
        return *this;
    }

    pos_type tellg()
    {
        pos_type pos = pos_type(off_type(-1));

        if(sentry(*this, true) && !this->fail())
            pos = this->rdbuf()->pubseekoff(0, ios_base::cur, ios_base::in);

        return pos;
    }

    basic_istream& seekg(pos_type pos)
    {
        this->clear(this->rdstate() & ~ios_base::eofbit);

        if(sentry(*this, true) && !this->fail())
        {
            if(this->rdbuf()->pubseekpos(pos, ios_base::in) 
                    == pos_type(off_type(-1)))
                this->setstate(ios_base::failbit);
        }

        return *this;
    }

    basic_istream& seekg(off_type off, ios_base::seekdir dir)
    {
        this->clear(this->rdstate() & ~ios_base::eofbit);

        if(sentry(*this, true) && !this->fail())
        {
            if(this->rdbuf()->pubseekoff(off, dir, ios_base::in) 
                    == pos_type(off_type(-1)))
                this->setstate(ios_base::failbit);
        }

        return *this;
    }

    //TODO other unformatted input

protected:
    basic_istream(const basic_istream&) = delete;
    basic_istream(basic_istream&& rhs) = default;

    void swap(basic_istream& rhs)
    {
        std::swap(*this, rhs);
    }

private:
    [[no_unique_address]] detail::gcount_storage<NEVER_SET_GCOUNT> get_count;
};

} //namespace std

#endif //STD_ISTREAM_HPP
