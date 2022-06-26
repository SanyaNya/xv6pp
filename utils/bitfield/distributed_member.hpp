#ifndef XV6PP_UTILS_BITFILED_DISTRIBUTED_MEMBER_HPP
#define XV6PP_UTILS_BITFILED_DISTRIBUTED_MEMBER_HPP

#include "../../libcpp/cstddef.hpp"
#include "../../libcpp/cstdint.hpp"
#include "../../libcpp/bit.hpp"
#include "../../libcpp/new.hpp"
#include "../../libcpp/utility.hpp"
#include "../equal_integral_rank.hpp"
#include "part.hpp"
#include "helper_functions.hpp"

namespace xv6pp
{

template<typename T, std::integral int_type, Part ... PARTS>
struct distributed_member
{
    constexpr distributed_member() noexcept = default;

    distributed_member(T t) noexcept
    {
        *this = t;
    }

    distributed_member& operator=(T t) noexcept
    {
        const int_type t_int = 
            static_cast<int_type>(std::bit_cast<TInt>(t));

        storage() &= storage_inv_mask;
        storage() |= merge_parts_from_src(t_int);

        return *this;
    }

    operator T() const noexcept
    {
        int_type result = merge_parts_from_storage(storage());
        
        return std::bit_cast<T>(static_cast<TInt>(result));
    }

private:
    int_type& storage() noexcept
    {
        return *std::launder(reinterpret_cast<int_type*>(this));
    }

    const int_type& storage() const noexcept
    {
        return *std::launder(reinterpret_cast<const int_type*>(this));
    }

    using TInt = equal_integral_rank_t<T>;

    static constexpr Part parts[] = { PARTS... };

    static constexpr int_type storage_inv_mask = 
        ~(detail::mask<int_type>(PARTS.begin, PARTS.end) | ...);

    static constexpr std::size_t BYTE_SIZE = 
        std::numeric_limits<std::underlying_type_t<std::byte>>::digits();

    static constexpr int_type merge_parts_from_src(int_type src) noexcept
    {
        return 
            [src]<std::size_t ... Is>(std::index_sequence<Is...>)
            {
                return ([src]()
                        {
                            constexpr auto mask = 
                                detail::mask<int_type>(
                                        parts[Is].begin, 
                                        parts[Is].end);

                            const auto r = 
                                detail::shift_to<
                                    flat_offset(Is, parts),
                                    parts[Is].begin>(src);

                            return r & mask;
                        }() | ...);
            }(std::make_index_sequence<sizeof...(PARTS)>());
    }

    static constexpr int_type merge_parts_from_storage(int_type src) noexcept
    {
        return 
            [src]<std::size_t ... Is>(std::index_sequence<Is...>)
            {
                return ([src]()
                        {
                            constexpr auto mask = 
                                detail::mask<int_type>(
                                        flat_offset(Is, parts), 
                                        flat_offset(Is+1, parts));

                            const auto r = 
                                detail::shift_to<
                                    parts[Is].begin,
                                    flat_offset(Is, parts)>(src);

                            return r & mask;
                        }() | ...);
            }(std::make_index_sequence<sizeof...(PARTS)>());
    }
};

} //namespace xv6pp

#endif //XV6PP_UTILS_BITFILED_DISTRIBUTED_MEMBER_HPP
