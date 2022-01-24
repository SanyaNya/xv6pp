#ifndef STD_SPAN_HPP
#define STD_SPAN_HPP

#include "cstddef.hpp"
#include "type_traits.hpp"
#include "limits.hpp"
#include "array.hpp"

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

} //namesapce

template<typename T, std::size_t Extent = dynamic_extent>
class span
{
public:
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
    
    constexpr iterator begin() const noexcept
    {
        return ptr;
    }

    constexpr iterator end() const noexcept
    {
        return ptr+extent_wrapper.get();
    }

    constexpr pointer data() const noexcept
    {
        return ptr;
    }

    constexpr reference operator[](size_type idx) const
    {
        return ptr[idx];
    }

    constexpr size_type size() const noexcept
    {
        return extent_wrapper.get();
    }

    constexpr size_type size_bytes() const noexcept
    {
        return size() * sizeof(element_type);
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
