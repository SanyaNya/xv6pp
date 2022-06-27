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
    constexpr adv_bitfield(TAlias t) noexcept : storage(t) {}

    constexpr TImpl& operator=(TAlias t) noexcept
    {
        storage = t;
        return *static_cast<TImpl*>(this);
    }

    constexpr operator TAlias() const noexcept
    {
        return storage;
    }

private:
    TAlias storage;
};

} //namespace xv6pp

#endif //XV6PP_UTILS_ADV_BITFIELD_HPP
