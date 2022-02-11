#ifndef STD_IOS_IMPL_BASIC_IOS_HPP
#define STD_IOS_IMPL_BASIC_IOS_HPP

#include "../string_impl/char_traits.hpp"
#include "../streambuf.hpp"
#include "../ios_impl/ios_base.hpp"
#include "../exception.hpp"

namespace std
{

namespace detail
{

template<bool NEVER_CHECK_IOSTATE>
struct iostate_storage
{
    constexpr ios_base::iostate get() const { return state; }
    constexpr void set(ios_base::iostate s) { state = s; }

private:
    ios_base::iostate state;
};

template<>
struct iostate_storage<true>
{
    constexpr ios_base::iostate get() const { return ios_base::goodbit; }
    constexpr void set(ios_base::iostate) {}
};

} //namespace detail

template<
    typename CharT, 
    typename Traits = char_traits<CharT>,
    bool NEVER_CHECK_IOSTATE = false,
    typename TImpl = void,
    typename TStreambufImpl = void>
class basic_ios : public ios_base_crtp<TImpl>
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

    ios_base::iostate rdstate() const
    {
        return io_state.get();
    }

    void clear(ios_base::iostate state = ios_base::goodbit)
    {
        if(rdbuf() != 0) io_state.set(state);
        else io_state.set(state | ios_base::badbit);

        if((rdstate() & exceptions()) != ios_base::goodbit)
            terminate(); //TODO exception throw
    }
    
    void setstate(ios_base::iostate state)
    {
        clear(rdstate() | state);
    }

    bool good() const
    {
        return rdstate() == ios_base::goodbit;
    }

    bool eof() const
    {
        return static_cast<bool>(rdstate() & ios_base::goodbit);
    }

    bool fail() const
    {
        return static_cast<bool>(rdstate() & ios_base::failbit);
    }

    bool bad() const
    {
        return static_cast<bool>(rdstate() & ios_base::badbit);
    }

    ios_base::iostate exceptions() const
    {
        return exceptions_mask.get();
    }

    void exceptions(ios_base::iostate except)
    {
        exceptions_mask.set(except);
        clear(rdstate());
    }

    //constructor/destructor
    explicit basic_ios(basic_streambuf<CharT, Traits, TStreambufImpl>* sb)
    {
        init(sb);
    }

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
        io_state.set(sb ? ios_base::goodbit : ios_base::badbit);
        exceptions_mask.set(ios_base::goodbit);
    }

    void move(basic_ios& rhs)
    {
        io_state.set(rhs.io_state);
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
    
    [[no_unique_address]] 
    detail::iostate_storage<NEVER_CHECK_IOSTATE> io_state;
    
    [[no_unique_address]]
    detail::iostate_storage<NEVER_CHECK_IOSTATE> exceptions_mask;
};

} //namesapce std

#endif //STD_IOS_IMPL_BASIC_IOS_HPP
