#ifndef STD_ALLOCATOR_HPP
#define STD_ALLOCATOR_HPP

#include "type_traits_impl/bool_constant.hpp"
#include "cstddef_impl/types.hpp"
#include "new.hpp"

namespace std
{

template<typename T>
class allocator
{
public:
    using value_type                             = T;
    using size_type                              = size_t;
    using difference_type                        = ptrdiff_t;
    using propagate_on_container_move_assignment = true_type;
    using is_always_equal                        = true_type;

    constexpr allocator() noexcept = default;
    constexpr allocator(const allocator&) noexcept = default;
    template<typename U> constexpr allocator(const allocator<U>&) noexcept {}
    constexpr ~allocator() = default;
    constexpr allocator& operator=(const allocator&) = default;

    [[nodiscard]] constexpr T* allocate(size_t n)
    {
        //TODO throw bad_array_new_length
        return static_cast<T*>(
                ::operator new(n * sizeof(T), align_val_t(alignof(T))));
    }

    constexpr void deallocate(T* p, size_t n)
    {
        ::operator delete(p, n * sizeof(T), align_val_t(alignof(T)));
    }
};

template<typename T, typename U>
constexpr bool operator==(const allocator<T>&, const allocator<T>&)
{ 
    return true;
}

} //namespace mem

#endif //STD_ALLOCATOR_HPP
