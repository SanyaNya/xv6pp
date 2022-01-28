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
class basic_rawbuf : public std::basic_streambuf<CharT, traits>
{
    using base = std::basic_streambuf<CharT, traits>;

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

        base::setg(buf_begin, buf_begin, buf_end);
        base::setp(buf_begin, buf_end);

        buffer_update(pos);
    }

    virtual ~basic_rawbuf()
    {
        allocator.deallocate(buffer(), detail::BUFFER_SIZE);
    }

    virtual pos_type seekoff(
                off_type offset, 
                std::ios_base::seekdir dir, 
                std::ios_base::openmode = 
                    std::ios_base::in | std::ios_base::out) override
    {
        switch(dir)
        {
            case std::ios_base::beg: return seekpos(offset);
            case std::ios_base::cur: return seekpos(cur_pos() + offset);
            //case std::ios_base::end:  //TODO

            default: return pos_type(off_type(-1));
        }
    }

    virtual pos_type seekpos(
                pos_type pos, 
                std::ios_base::openmode = 
                    std::ios_base::in | std::ios_base::out) override
    {
        if(base::sync() == -1) return pos_type(off_type(-1));    

        buffer_update(pos);

        return pos;
    }

    virtual int sync() override
    {
        //TODO
        return 0;
    }

    virtual int_type underflow() override
    {
        if(seekpos(cur_pos()))
            return traits::to_int_type(*buffer());

        return traits::eof();
    }

    //TODO overflow

private:
   [[no_unique_address]] Allocator allocator;
   pos_type buf_base_sector_pos;

   //put pos == get pos
   pos_type cur_pos() const
   { 
       return buf_base_sector_pos*detail::SECTOR_SIZE + (base::gptr() - base::eback()); 
   }

   //eback == pbase
   char_type* buffer() const { return base::in_begin; }
   void buffer(char_type* buf) { base::in_begin = buf; }

   void buffer_update(pos_type pos)
   {
       buf_base_sector_pos = pos / detail::SECTOR_SIZE;

       detail::read(buffer(), buf_base_sector_pos);

       base::in_cur  = buffer() + (pos % detail::SECTOR_SIZE);
       base::out_cur = buffer() + (pos % detail::SECTOR_SIZE);
   }
};

using rawbuf = basic_rawbuf<char>;

} //namespace xv6pp::io

#endif //XV6PP_IO_RAW_STREAMBUF_HPP
