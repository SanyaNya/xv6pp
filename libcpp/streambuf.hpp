#ifndef STD_STREAMBUF_HPP
#define STD_STREAMBUF_HPP

#include "string_impl/char_traits.hpp"
#include "ios_impl/ios_base.hpp"
#include "algorithm.hpp"

#ifndef STD_CRTP_STREAMBUF
#define STD_STREAMBUF_VIRTUAL virtual
#define STD_STREAMBUF_OVERRIDE override
#else
#define STD_STREAMBUF_VIRTUAL 
#define STD_STREAMBUF_OVERRIDE 
#endif

namespace std
{

template<
    typename CharT, 
    typename traits = char_traits<CharT>,
    typename TImpl = void>
class basic_streambuf
{
    constexpr auto& get_this()
    {
#ifdef STD_CRTP_STREAMBUF
        return *static_cast<TImpl*>(this);
#else
        return *this;
#endif
    }

public:
    using char_type   = CharT;
    using int_type    = typename traits::int_type;
    using pos_type    = typename traits::pos_type;
    using off_type    = typename traits::off_type;
    using traits_type = traits;

    STD_STREAMBUF_VIRTUAL ~basic_streambuf() = default;
    
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
        in_begin(nullptr),
        in_cur(nullptr),
        in_end(nullptr),
        out_begin(nullptr),
        out_cur(nullptr),
        out_end(nullptr) {}

    basic_streambuf(const basic_streambuf& rhs) = default;
    basic_streambuf& operator=(const basic_streambuf& rhs) = default;

    void swap(basic_streambuf& rhs)
    {
        std::swap(*this, rhs);
    }

    //get area access
    //guaranteed to be 
    //(eback() != nullptr && 
    // gptr()  != nullptr && 
    // egptr() != nullptr) ||
    //(eback() == nullptr &&
    // gptr()  == nullptr &&
    // egptr() == nullptr)
    char_type* eback() const { return in_begin; }
    char_type* gptr()  const { return in_cur;   }
    char_type* egptr() const { return in_end;   }

    void gbump(int n) { in_cur += n; }
    
    void setg(char_type* gbeg, char_type* gnext, char_type* gend)
    {
        in_begin = gbeg;
        in_cur = gnext;
        in_end = gend;
    }

    //put area access
    //guaranteed to be 
    //(pbase() != nullptr && 
    // pptr()  != nullptr && 
    // epptr() != nullptr) ||
    //(pbase() == nullptr &&
    // pptr()  == nullptr &&
    // epptr() == nullptr)
    char_type* pbase() const { return out_begin; }
    char_type* pptr()  const { return out_cur;   }
    char_type* epptr() const { return out_end;   }

    void pbump(int n) { out_cur += n; }

    void setp(char_type* pbeg, char_type* pend)
    {
        out_begin = pbeg;
        out_cur = pbeg;
        out_end = pend;
    }

    //virtual functions

    //locales
    //virtual void imbue(const locale&) {} TODO
    
    //buffer management and positioning
    STD_STREAMBUF_VIRTUAL basic_streambuf* setbuf(char_type*, streamsize) { return this; }

    STD_STREAMBUF_VIRTUAL pos_type seekoff(
                off_type, 
                ios_base::seekdir,
                ios_base::openmode = ios_base::in | ios_base::out)
    {
        return pos_type(off_type(-1));
    }
    
    STD_STREAMBUF_VIRTUAL pos_type seekpos(
                pos_type, 
                ios_base::openmode = ios_base::in | ios_base::out)
    {
        return pos_type(off_type(-1));
    }

    STD_STREAMBUF_VIRTUAL int sync() { return 0; }

    //get area
    STD_STREAMBUF_VIRTUAL streamsize showmanyc() { return 0; }

    STD_STREAMBUF_VIRTUAL streamsize xsgetn(char_type* s, streamsize n)
    {
        streamsize ret = n;
        do
        {
            const streamsize count = std::min(n, egptr() - gptr());
            traits::copy(s, gptr(), count);
            s   += count;
            n   -= count;
            gbump_streamsize(count);
        }
        while(n != 0 && !traits::eq_int_type(get_this().underflow(), traits::eof()));

        return ret-n;
    }
    
    STD_STREAMBUF_VIRTUAL int_type underflow() { return traits::eof(); }

    STD_STREAMBUF_VIRTUAL int_type uflow()
    {
        return !traits::eq_int_type(get_this().underflow(), traits::eof()) ? *in_cur++ : traits::eof();
    }

    //putback
    STD_STREAMBUF_VIRTUAL int_type pbackfail(int_type = traits::eof())
    {
        return traits::eof();
    }

    //put area
    STD_STREAMBUF_VIRTUAL streamsize xsputn(const char_type* s, streamsize n)
    {
        streamsize ret = n;
        while(n != 0)
        {
            const streamsize count = std::min(n, epptr() - pptr());
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

    STD_STREAMBUF_VIRTUAL int_type overflow(int_type = traits::eof())
    {
        return traits::eof();
    }

    char_type* in_begin;
    char_type* in_cur;
    char_type* in_end;

    char_type* out_begin;
    char_type* out_cur;
    char_type* out_end;

    bool is_read_avail() const
    {
        //gptr() < egptr() is enough
        //even if gptr() == nullptr and egptr() == nullptr
        return /*gptr() == nullptr  && 
                 egptr() == nullptr &&*/ 
                 gptr() < egptr();
    }

    bool is_putback_avail() const
    {
        //eback() < egptr() is enough
        //even if eback() == nullptr and egptr() == nullptr
        return /*eback() == nullptr && 
                 egptr() == nullptr &&*/ 
                 eback() < egptr();
    }

    bool is_put_avail() const
    {
        //pptr() < epptr() is enough
        //even if pptr() == nullptr and epptr() == nullptr
        return /*pptr() == nullptr  && 
                 epptr() == nullptr &&*/ 
                 pptr() < epptr();
    }

    void gbump_streamsize(streamsize n) { in_cur += n; }
    void pbump_streamsize(streamsize n) { out_cur += n; }
};

using streambuf = basic_streambuf<char>;
//TODO wstreambuf

} //namespace std

#endif //STD_STREAMBUF_HPP
