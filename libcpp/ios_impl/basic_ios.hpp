#ifndef STD_IOS_IMPL_BASIC_IOS_HPP
#define STD_IOS_IMPL_BASIC_IOS_HPP

#include "../string_impl/char_traits.hpp"
#include "../streambuf.hpp"
#include "../ios_impl/ios_base.hpp"
#include "../exception.hpp"

namespace std
{

template<
    typename CharT, 
    typename Traits = char_traits<CharT>, 
    typename TStreambufImpl = void>
class basic_ios : public ios_base
{
public:
    using char_type   = CharT;
    using int_type    = typename Traits::int_type;
    using pos_type    = typename Traits::pos_type;
    using off_type    = typename Traits::off_type;
    using traits_type = Traits;

    //flags functions
    explicit operator bool() const
    {
        return !fail();
    }

    bool operator!() const
    {
        return fail();
    }

    iostate rdstate() const
    {
        return io_state;
    }

    void clear(iostate state = goodbit)
    {
        if(rdbuf() != 0) io_state = state;
        else io_state = state | badbit;

        if(rdstate() & exceptions())
            terminate(); //TODO exception throw
    }
    
    void setstate(iostate state)
    {
        clear(rdstate() | state);
    }

    bool good() const
    {
        return rdstate() == 0;
    }

    bool eof() const
    {
        return static_cast<bool>(rdstate() & iostate::goodbit);
    }

    bool fail() const
    {
        return static_cast<bool>(rdstate() & iostate::failbit);
    }

    bool bad() const
    {
        return static_cast<bool>(rdstate() & iostate::badbit);
    }

    iostate exceptions() const
    {
        return exceptions_mask;
    }

    void exceptions(iostate except)
    {
        exceptions_mask = except;
        clear(rdstate());
    }

    //constructor/destructor
    explicit basic_ios(basic_streambuf<CharT, Traits, TStreambufImpl>* sb)
    {
        init(sb);
    }
    virtual ~basic_ios() = default;

    //members
    basic_streambuf<CharT, Traits, TStreambufImpl>* rdbuf() const
    {
        return buf;
    }

    basic_streambuf<CharT, Traits, TStreambufImpl>* 
        rdbuf(basic_streambuf<CharT, Traits, TStreambufImpl>* sb)
    {
        auto* prev_buf = rdbuf();

        buf = sb;
        clear();

        return prev_buf;
    }

    basic_ios(const basic_ios&) = delete;
    basic_ios& operator=(const basic_ios&) = delete;
protected:
    basic_ios() = default;
    void init(basic_streambuf<CharT, Traits, TStreambufImpl>* sb)
    {
        buf = sb;
        io_state = sb ? goodbit : badbit;
        exceptions_mask = goodbit;
    }

    void move(basic_ios& rhs)
    {
        io_state = rhs.io_state;
        buf = nullptr;
    }

    void move(basic_ios&& rhs)
    {
        move(rhs);
    }

    void swap(basic_ios& rhs) noexcept
    {
        swap(io_state, rhs.io_state);
    }

    void set_rdbuf(basic_streambuf<CharT, Traits, TStreambufImpl>* sb)
    {
        if(sb != nullptr) buf = sb;
    }

private:
    basic_streambuf<CharT, Traits, TStreambufImpl>* buf;
    iostate io_state;
    iostate exceptions_mask;
};

} //namesapce std

#endif //STD_IOS_IMPL_BASIC_IOS_HPP
