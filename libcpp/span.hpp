#ifndef STD_SPAN_HPP
#define STD_SPAN_HPP

#include "cstddef.hpp"
#include "type_traits.hpp"
#include "limits.hpp"
#include "array.hpp"
#include "exception.hpp"

namespace std
{

inline constexpr std::size_t dynamic_extent 
    = std::numeric_limits<std::size_t>::max();

namespace
{

template<std::size_t Extent>
class extent_storage
{
public:
    constexpr extent_storage(std::size_t) noexcept {}

    constexpr std::size_t get() const noexcept
    {
        return Extent;
    }
};

template<>
class extent_storage<dynamic_extent>
{
    std::size_t extent;

public:
    constexpr extent_storage(std::size_t ext) noexcept
        : extent(ext) {}

    constexpr std::size_t get() const noexcept
    {
        return extent;
    }
};

template<size_t Extent, size_t Offset, size_t Count>
    static constexpr size_t subspan_size = 
        Count != dynamic_extent ? Count
                                : (Extent != dynamic_extent ? Extent - Offset
                                                            : dynamic_extent);

} //namesapce

template<typename T, std::size_t Extent = dynamic_extent>
class span
{
public:
    //constants and types
    using element_type    = T;
    using value_type      = std::remove_cv_t<T>;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer         = T*;
    using const_pointer   = const T*;
    using reference       = T&;
    using const_reference = const T&;
    using iterator        = pointer;
    using const_iterator  = const_pointer;
    //using reverse_iterator =       //TODO
    //using const_reverse_iterator = //

    static constexpr std::size_t extent = Extent;

    //constructors, copy and assignment
    constexpr span() noexcept
        requires (extent == 0 || extent == dynamic_extent)
        : ptr(nullptr), extent_wrapper(0) {}

    //TODO Generic iterator
    explicit(extent != dynamic_extent)
    constexpr span(iterator it, size_type count)
        : ptr(it), extent_wrapper(count) {}

    explicit(extent != dynamic_extent)
    constexpr span(iterator beg, iterator end)
        : ptr(beg), extent_wrapper(static_cast<size_type>(end-beg)) {}

    template<std::size_t N>
        requires(extent == dynamic_extent || extent == N)
    constexpr span(element_type (&arr)[N]) noexcept
        : span(static_cast<pointer>(arr), N) {}

    template<typename U, std::size_t N>
        requires((extent == dynamic_extent || extent == N) &&
                 is_convertible_v<U(*)[], T(*)[]>)
    constexpr span(array<U, N>& arr) noexcept 
        : span(static_cast<pointer>(arr.data()), N) {}

    template<typename U, std::size_t N>
        requires((extent == dynamic_extent || extent == N) &&
                 is_convertible_v<const U(*)[], T(*)[]>)
    constexpr span(const array<U, N>& arr) noexcept
        : span(static_cast<pointer>(arr.data()), N) {}

    //TODO other ctors
    
    //subviews
    template<size_t Offset, size_t Count = dynamic_extent>
    constexpr span<element_type, subspan_size<Extent, Offset, Count>> subspan() const
    {
        if constexpr(Extent != dynamic_extent)
        {
            static_assert(Offset <= Extent);
            static_assert(Count == dynamic_extent || Count <= (Extent - Offset));
        }
        else
        {
            detail::assert(Offset <= size());
            detail::assert(Count == dynamic_extent || Count <= (size() - Offset));
        }

        return span<element_type, subspan_size<Extent, Offset, Count>>(
                data() + Offset, 
                Count != dynamic_extent ? Count : size() - Offset);
    }

    //observers
    constexpr size_type size() const noexcept
    {
        return extent_wrapper.get();
    }

    constexpr size_type size_bytes() const noexcept
    {
        return size() * sizeof(element_type);
    }

    //element access
    constexpr reference operator[](size_type idx) const
    {
        detail::assert(idx < size());
        return ptr[idx];
    }

    constexpr reference front() const
    {
        if constexpr(Extent != dynamic_extent)
            static_assert(Extent != 0);
        else
            detail::assert(size() != 0);

        return ptr[0];
    }

    constexpr reference back() const
    {
        if constexpr(Extent != dynamic_extent)
            static_assert(Extent != 0);
        else
            detail::assert(size() != 0);

        return ptr[size()-1];
    }

    constexpr pointer data() const noexcept
    {
        return ptr;
    }

    //iterator support
    constexpr iterator begin() const noexcept
    {
        return ptr;
    }

    constexpr iterator end() const noexcept
    {
        return ptr+extent_wrapper.get();
    }
private:
    pointer ptr;
    [[no_unique_address]] extent_storage<Extent> extent_wrapper;
};

template<typename T, size_t N>
span(T (&)[N]) -> span<T, N>;

template<typename T, size_t N>
span(array<T, N>&) -> span<T, N>;

template<typename T, size_t N>
span(const array<T, N>&) -> span<T, N>;

} //namespace std

#endif //STD_SPAN_HPP
