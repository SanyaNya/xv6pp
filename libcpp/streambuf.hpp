#ifndef STD_STREAMBUF_HPP
#define STD_STREAMBUF_HPP

#include "string_impl/char_traits.hpp"
#include "ios_impl/ios_base.hpp"
#include "algorithm.hpp"
#include "span.hpp"

namespace std
{

namespace detail
{

template<bool B, typename TImpl, typename traits>
class streambuf_enable_virtual {};

template<typename TImpl, typename traits>
class streambuf_enable_virtual<true, TImpl, traits>
{
    using char_type   = typename traits::char_type;
    using int_type    = typename traits::int_type;
    using pos_type    = typename traits::pos_type;
    using off_type    = typename traits::off_type;
    using traits_type = traits;

public:
    virtual ~streambuf_enable_virtual() = default;

protected:
    virtual TImpl* setbuf(char_type* b, streamsize size) = 0;

    virtual pos_type seekoff(
            off_type off,
            ios_base::seekdir dir,
            ios_base::openmode mode = ios_base::in | ios_base::out) = 0;

    virtual pos_type seekpos(
                pos_type pos, 
                ios_base::openmode mode = ios_base::in | ios_base::out) = 0;

    virtual int sync() = 0;
    virtual streamsize showmanyc() = 0;
    virtual streamsize xsgetn(char_type* s, streamsize n) = 0;
    virtual int_type underflow() = 0;
    virtual int_type uflow() = 0;
    virtual int_type pbackfail(int_type c = traits_type::eof()) = 0;
    virtual streamsize xsputn(const char_type* s, streamsize n) = 0;
    virtual int_type overflow(int_type c = traits_type::eof()) = 0;
};

} //namespace detail

template<
    typename CharT, 
    typename traits = char_traits<CharT>,
    size_t InExtent = dynamic_extent,
    size_t OutExtent = dynamic_extent,
    typename TImpl = void>
class basic_streambuf : 
    public detail::streambuf_enable_virtual<
        is_same_v<TImpl, void>, 
        basic_streambuf<CharT, traits, InExtent, OutExtent, TImpl>,
        traits>
{
    static constexpr bool IS_CRTP = !is_same_v<TImpl, void>;

    constexpr auto& get_this()
    {
        if constexpr(IS_CRTP)
            return *static_cast<TImpl*>(this);
        else 
            return *this;
    }

public:
    using char_type   = CharT;
    using int_type    = typename traits::int_type;
    using pos_type    = typename traits::pos_type;
    using off_type    = typename traits::off_type;
    using traits_type = traits;

    //locales
    //locale pubimbue(const locale& loc) TODO
    //locale getloc() const TODO

    //buffer and positioning
    basic_streambuf* pubsetbuf(char_type* s, streamsize n)
    {
        return get_this().setbuf(s, n);
    }

    pos_type pubseekoff(
                off_type off, 
                ios_base::seekdir way,
                ios_base::openmode which = 
                    ios_base::in | ios_base::out)
    {
        return get_this().seekoff(off, way, which);
    }

    pos_type pubseekpos(
                pos_type sp,
                ios_base::openmode which =
                    ios_base::in | ios_base::out)
    {
        return get_this().seekpos(sp, which);
    }

    int pubsync()
    {
        return get_this().sync();
    }

    //get and put areas
    streamsize in_avail()
    {
        const streamsize avail = egptr() - gptr();
        return avail > 0 ? avail : get_this().showmanyc();
    }

    int_type snextc()
    {
        [[likely]] if(!traits::eq_int_type(sbumpc(), traits::eof()))
            return sgetc();
        return traits::eof();
    }

    int_type sbumpc()
    {
        [[likely]] if(is_read_avail())
            return traits::to_int_type(*in_cur++);
        return get_this().uflow();
    }

    int_type sgetc()
    {
        [[likely]] if(is_read_avail())
            return traits::to_int_type(*gptr());
        return get_this().underflow();
    }

    streamsize sgetn(char_type* s, streamsize n)
    {
        return get_this().xsgetn(s, n);
    }

    //putback
    int_type sputbackc(char_type c)
    {
        [[likely]] if(is_putback_avail() && traits::eq(c, gptr()[-1]))
            return traits::to_int_type(*--in_cur);
        return get_this().pbackfail(traits::to_int_type(c));
    }
    
    int_type sungetc()
    {
        [[likely]] if(is_putback_avail())
            return traits::to_int_type(*--in_cur);
        return get_this().pbackfail();
    }

    //put area
    int_type sputc(char_type c)
    {
        [[likely]] if(is_put_avail())
            return traits::to_int_type(*out_cur++ = c);
        return get_this().overflow(traits::to_int_type(c));
    }

    streamsize sputn(const char_type* s, streamsize n)
    {
        return get_this().xsputn(s, n);
    }

protected:
    basic_streambuf() : 
        in_span(nullptr, nullptr),
        in_cur(nullptr),
        out_span(nullptr, nullptr),
        out_cur(nullptr) {}

    basic_streambuf(span<char_type, InExtent> s) : 
        in_span(s),
        out_span(s) {}

    basic_streambuf(const basic_streambuf& rhs) = default;
    basic_streambuf& operator=(const basic_streambuf& rhs) = default;

    void swap(basic_streambuf& rhs)
    {
        swap(in_span, rhs.in_span);
        swap(in_cur,   rhs.in_cur);

        swap(out_span, rhs.out_span);
        swap(out_cur,   rhs.out_cur);
    }

    //get area access
    //guaranteed to be 
    //(eback() != nullptr && 
    // gptr()  != nullptr && 
    // egptr() != nullptr) ||
    //(eback() == nullptr &&
    // gptr()  == nullptr &&
    // egptr() == nullptr)
    char_type* eback() const { return in_span.begin(); }
    char_type* gptr()  const { return in_cur;   }
    char_type* egptr() const { return in_span.end();   }

    void gbump(int n) { in_cur += n; }
    
    void setg(char_type* gbeg, char_type* gnext, char_type* gend)
    {
        //gend ignored if InExtent != dynamic_extent
        in_span = span<char_type, InExtent>(gbeg, gend);
        in_cur = gnext;
    }

    //put area access
    //guaranteed to be 
    //(pbase() != nullptr && 
    // pptr()  != nullptr && 
    // epptr() != nullptr) ||
    //(pbase() == nullptr &&
    // pptr()  == nullptr &&
    // epptr() == nullptr)
    char_type* pbase() const { return out_span.begin(); }
    char_type* pptr()  const { return out_cur;   }
    char_type* epptr() const { return out_span.end();   }

    void pbump(int n) { out_cur += n; }

    void setp(char_type* pbeg, char_type* pend)
    {
        //pend ignored if OutExtent != dynamic_extent
        out_span = span<char_type, OutExtent>(pbeg, pend);
        out_cur = pbeg;
    }

    //virtual functions

    //locales
    //virtual void imbue(const locale&) {} TODO
    
    //buffer management and positioning
    basic_streambuf* setbuf(char_type*, streamsize) { return this; }

    pos_type seekoff(
                off_type, 
                ios_base::seekdir,
                ios_base::openmode = ios_base::in | ios_base::out)
    {
        return pos_type(off_type(-1));
    }
    
    pos_type seekpos(
                pos_type, 
                ios_base::openmode = ios_base::in | ios_base::out)
    {
        return pos_type(off_type(-1));
    }

    int sync() { return 0; }

    //get area
    streamsize showmanyc() { return 0; }

    streamsize xsgetn(char_type* s, streamsize n)
    {
        streamsize ret = n;
        do
        {
            const streamsize count = min(n, egptr() - gptr());
            traits::copy(s, gptr(), count);
            s   += count;
            n   -= count;
            gbump_streamsize(count);
        }
        while(n != 0 && !traits::eq_int_type(get_this().underflow(), traits::eof()));

        return ret-n;
    }
    
    int_type underflow() { return traits::eof(); }

    int_type uflow()
    {
        return !traits::eq_int_type(get_this().underflow(), traits::eof()) ? *in_cur++ : traits::eof();
    }

    //putback
    int_type pbackfail(int_type = traits::eof())
    {
        return traits::eof();
    }

    //put area
    streamsize xsputn(const char_type* s, streamsize n)
    {
        streamsize ret = n;
        while(n != 0)
        {
            const streamsize count = min(n, epptr() - pptr());
            traits::copy(pptr(), s, count);
            s += count;
            n -= count;
            pbump_streamsize(count);

            if(n != 0 && !traits::eq_int_type(get_this().overflow(traits::to_int_type(*out_cur)), traits::eof()))
            {
                s++;
                n--;
                out_cur++;
            }
        }

        return ret-n;
    }

    int_type overflow(int_type = traits::eof())
    {
        return traits::eof();
    }

private:
    span<char_type, InExtent> in_span;
    char_type* in_cur;

    span<char_type, OutExtent> out_span;
    char_type* out_cur;

    bool is_read_avail() const
    {
        if constexpr (InExtent == dynamic_extent)
            return gptr() < egptr();
        else
            return gptr() && (gptr() < egptr());
    }

    bool is_putback_avail() const
    {
        if constexpr(InExtent == dynamic_extent)
            return eback() < gptr();
        else
            return gptr() && (eback() < gptr());
    }

    bool is_put_avail() const
    {
        if constexpr(OutExtent == dynamic_extent)
            return pptr() < epptr();
        else
            return pptr() && (pptr() < epptr());
    }

    void gbump_streamsize(streamsize n) { in_cur += n; }
    void pbump_streamsize(streamsize n) { out_cur += n; }
};

using streambuf = basic_streambuf<char>;
//TODO wstreambuf

} //namespace std

#endif //STD_STREAMBUF_HPP
