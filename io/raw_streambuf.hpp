#ifndef XV6PP_IO_RAW_STREAMBUF_HPP
#define XV6PP_IO_RAW_STREAMBUF_HPP

#include "../libcpp/streambuf.hpp"
#include "../libcpp/allocator.hpp"
#include "ATA_PIO_LBA28_Disk.hpp"

namespace xv6pp::io
{

template<
    typename CharT, 
    typename traits = std::char_traits<CharT>,
    typename Allocator = std::allocator<CharT>>
class basic_rawbuf final : public std::basic_streambuf<CharT, traits, basic_rawbuf<CharT, traits, Allocator>>
{
    using base = std::basic_streambuf<CharT, traits, basic_rawbuf<CharT, traits, Allocator>>;
    friend base;

public:
    using char_type   = CharT;
    using int_type    = typename traits::int_type;
    using pos_type    = typename traits::pos_type;
    using off_type    = typename traits::off_type;
    using traits_type = traits;

    basic_rawbuf(pos_type pos)
    {
        char_type* const buf_begin = allocator.allocate(detail::BUFFER_SIZE);
        char_type* const buf_end   = buf_begin + detail::BUFFER_SIZE;

        base::in_begin = buf_begin;
        base::in_end = buf_end;

        base::out_begin = buf_begin;
        base::out_end = buf_end;

        buffer_update(pos);
    }

    ~basic_rawbuf()
    {
        allocator.deallocate(buffer(), detail::BUFFER_SIZE);
    }

#ifndef STD_CRTP_STREAMBUF
    pos_type pubseekpos(pos_type pos, std::ios_base::openmode = std::ios_base::in | std::ios_base::out)
    {
        return seekpos(pos);
    }

    std::streamsize sgetn(char_type* s, std::streamsize n)
    {
        return base::sgetn(s, n);
    }
#endif

protected:
    pos_type seekoff(
                off_type offset, 
                std::ios_base::seekdir dir, 
                std::ios_base::openmode = 
                    std::ios_base::in | std::ios_base::out) STD_STREAMBUF_OVERRIDE
    {
        pos_type pos;
        switch(dir)
        {
            case std::ios_base::beg: pos = offset; break;
            case std::ios_base::cur: pos = cur_pos() + offset; break;
            case std::ios_base::end: pos = 0; break; //TODO
        }
        return seekpos(pos);
    }

    pos_type seekpos(
                pos_type pos, 
                std::ios_base::openmode = 
                    std::ios_base::in | std::ios_base::out) STD_STREAMBUF_OVERRIDE
    {
        buffer_update(pos);

        return pos;
    }

    int_type underflow() STD_STREAMBUF_OVERRIDE
    {
        seekpos(cur_pos());
        return traits::to_int_type(*buffer());
        //if(seekpos(cur_pos()) != pos_type(off_type(-1)))
        //    return traits::to_int_type(*buffer());

        //return traits::eof();
    }

    //TODO output

private:
   [[no_unique_address]] Allocator allocator;
   pos_type buf_base_pos;

   //put pos == get pos
   pos_type cur_pos() const
   { 
       return buf_base_pos + (base::gptr() - base::eback()); 
   }

   //eback == pbase
   char_type* buffer() const { return base::in_begin; }

   void buffer_update(pos_type pos)
   {
       buf_base_pos = pos - (pos % detail::SECTOR_SIZE);
       base::in_cur  = buffer() + (pos % detail::SECTOR_SIZE);
       base::out_cur = buffer() + (pos % detail::SECTOR_SIZE);

       detail::read(buffer(), pos / detail::SECTOR_SIZE);
   }
};

using rawbuf = basic_rawbuf<char>;

} //namespace xv6pp::io

#endif //XV6PP_IO_RAW_STREAMBUF_HPP
