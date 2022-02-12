#ifndef XV6PP_IO_RAWBUF_HPP
#define XV6PP_IO_RAWBUF_HPP

#include "../libcpp/streambuf.hpp"
#include "../libcpp/allocator.hpp"
#include "../libcpp/type_traits.hpp"
#include "ATA_PIO_LBA28_Disk.hpp"

namespace xv6pp::io
{

template<
    typename CharT, 
    typename traits = std::char_traits<CharT>,
    typename Allocator = std::allocator<CharT>>
class basic_rawbuf : 
    public std::basic_streambuf<
                CharT, traits, 
                basic_rawbuf<CharT, traits, Allocator>>
{
    using base = 
        std::basic_streambuf<
            CharT, traits, basic_rawbuf<CharT, traits, Allocator>>;
    friend base;

    using upos = std::make_unsigned_t<typename traits::pos_type>;

public:
    using char_type   = CharT;
    using int_type    = typename traits::int_type;
    using pos_type    = typename traits::pos_type;
    using off_type    = typename traits::off_type;
    using traits_type = traits;

    basic_rawbuf(upos pos)
    {
        char_type* const buf_begin = allocator.allocate(detail::BUFFER_SIZE);
        char_type* const buf_end   = buf_begin + detail::BUFFER_SIZE;

        base::in_begin = buf_begin;
        base::in_end = buf_end;

        base::out_begin = buf_begin;
        base::out_end = buf_end;

        buffer_update(pos);
    }

    basic_rawbuf(const basic_rawbuf&) = delete;
    basic_rawbuf(basic_rawbuf&&) = default;

    ~basic_rawbuf()
    {
        allocator.deallocate(buffer(), detail::BUFFER_SIZE);
    }

    basic_rawbuf& operator=(const basic_rawbuf&) = delete;
    basic_rawbuf& operator=(basic_rawbuf&&) = default;

    void swap(basic_rawbuf& rhs)
    {
        std::swap(*this, rhs);
    }

protected:
    pos_type seekoff(
                off_type offset, 
                std::ios_base::seekdir dir, 
                std::ios_base::openmode = 
                    std::ios_base::in | std::ios_base::out)
    {
        return seekpos(dir == std::ios_base::beg ? offset : offset + cur_pos());
    }

    pos_type seekpos(
                pos_type pos, 
                std::ios_base::openmode = 
                    std::ios_base::in | std::ios_base::out)
    {
        buffer_update(pos);

        return pos;
    }

    int_type underflow()
    {
        buffer_update(cur_pos());
        return traits::to_int_type(*buffer());
    }

    //TODO output

private:
   [[no_unique_address]] Allocator allocator;
   upos buf_base_pos;

   //put pos == get pos
   upos cur_pos() const
   { 
       return buf_base_pos + (base::gptr() - base::eback()); 
   }

   //eback == pbase
   char_type* buffer() const { return base::in_begin; }

   void buffer_update(upos pos)
   {
       buf_base_pos = detail::align_buf(pos);
       base::in_cur  = buffer() + detail::buf_align_indent(pos);
       base::out_cur = buffer() + detail::buf_align_indent(pos);

       detail::read(buffer(), detail::buf_sector(pos));
   }
};

using rawbuf = basic_rawbuf<char>;

} //namespace xv6pp::io

#endif //XV6PP_IO_RAWBUF_HPP
