#pragma once

#include "../libcpp/streambuf.hpp"
#include "../libcpp/allocator.hpp"
#include "../libcpp/type_traits.hpp"
#include "ATA_PIO_LBA28_Disk.hpp"

namespace xv6pp::io
{

template<
    typename CharT, 
    typename traits = std::char_traits<CharT>,
    template<typename> typename Allocator = std::allocator,
    bool CRTP = false,
    std::size_t InExtent = 4096,
    std::size_t OutExtent = 4096>
class basic_rawbuf final : 
    public std::basic_streambuf<
                CharT, traits, 
                InExtent, OutExtent,
                std::conditional_t<
                    CRTP,
                    basic_rawbuf<CharT, traits, Allocator, CRTP, InExtent, OutExtent>,
                    void>>
{
    using base = 
        std::basic_streambuf<
                CharT, traits, 
                InExtent, OutExtent,
                std::conditional_t<
                    CRTP,
                    basic_rawbuf<CharT, traits, Allocator, CRTP, InExtent, OutExtent>,
                    void>>;
    friend base;

    using upos = std::make_unsigned_t<typename traits::pos_type>;

public:
    using char_type   = CharT;
    using int_type    = typename traits::int_type;
    using pos_type    = typename traits::pos_type;
    using off_type    = typename traits::off_type;
    using traits_type = traits;

    explicit basic_rawbuf(upos pos) : 
        base(*allocator.allocate(1))
    {
        buffer_update(pos);
    }

    basic_rawbuf(const basic_rawbuf&) = delete;
    basic_rawbuf(basic_rawbuf&&) = default;

    ~basic_rawbuf()
    {
        allocator.deallocate(reinterpret_cast<std::array<char_type, InExtent>*>(buffer().data()), 1);
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
        return traits::to_int_type(*buffer().begin());
    }

    //TODO output

private:
   [[no_unique_address]] Allocator<std::array<char_type, InExtent>> allocator;
   upos buf_base_pos;

   //put pos == get pos
   upos cur_pos() const
   { 
       return buf_base_pos + (base::gptr() - base::eback()); 
   }

   //eback == pbase
   std::span<char_type, InExtent> buffer() const
   {
       return std::span<char_type, InExtent>(base::eback(), base::egptr());
   }

   void buffer_update(upos pos)
   {
       buf_base_pos = detail::align_buf(pos);

       base::setg(
            base::eback(), 
            base::eback() + detail::buf_align_indent(pos), 
            base::egptr());
       
       detail::read(buffer(), detail::buf_sector(pos));
   }
};

} //namespace xv6pp::io
