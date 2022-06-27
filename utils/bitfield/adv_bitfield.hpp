#ifndef XV6PP_UTILS_ADV_BITFIELD_HPP
#define XV6PP_UTILS_ADV_BITFIELD_HPP

#include "../../libcpp/bit.hpp"
#include "distributed_member.hpp"

namespace xv6pp
{

template<typename TImpl, typename TAlias>
struct adv_bitfield
{
    template<typename T, Part ... PARTS>
    using dm = distributed_member<T, TAlias, PARTS...>;

    constexpr adv_bitfield() noexcept = default;
    constexpr adv_bitfield(TAlias t) noexcept
    {
        *static_cast<TImpl*>(this) = std::bit_cast<TImpl>(t); 
    }

    constexpr TImpl& operator=(TAlias t) noexcept
    {
        return *static_cast<TImpl*>(this) = std::bit_cast<TImpl>(t);
    }

    constexpr operator TAlias() const noexcept
    {
        return std::bit_cast<TAlias>(*static_cast<const TImpl*>(this)); 
    }

private:
    TAlias storage;
};

} //namespace xv6pp

#endif //XV6PP_UTILS_ADV_BITFIELD_HPP
