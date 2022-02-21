#ifndef STD_UTILITY_IMPL_INTEGER_SEQUENCE_HPP
#define STD_UTILITY_IMPL_INTEGER_SEQUENCE_HPP

#include "../concepts.hpp"
#include "../type_traits_impl/type_identity.hpp"
#include "../type_traits_impl/integral_constant.hpp"

namespace std
{

template<integral T, T ... Is>
struct integer_sequence
{
    using value_type = T;
    static constexpr size_t size() { return sizeof...(Is); }
};

template<size_t ... Is>
using index_sequence = integer_sequence<size_t, Is...>;

namespace detail
{

template<typename T1, typename T2>
struct sequence_concat;

template<typename T, T ... Is1, T ... Is2>
struct sequence_concat<
    std::integer_sequence<T, Is1...>, 
    std::integer_sequence<T, Is2...>> :
        std::type_identity<std::integer_sequence<T, Is1..., Is2...>> {};

template<typename T1, typename T2>
using sequence_concat_t = typename sequence_concat<T1, T2>::type;

template<typename T>
struct make_seq_helper;

template<typename T, T N>
struct make_seq_helper<integral_constant<T, N>> : 
    type_identity<
        sequence_concat_t<
            typename make_seq_helper<integral_constant<T, N-1>>::type, 
            integer_sequence<T, N>>> {};

template<typename T>
struct make_seq_helper<integral_constant<T, static_cast<T>(-1)>> :
    type_identity<integer_sequence<T>> {};

template<typename T>
using make_seq_helper_t = typename make_seq_helper<T>::type;

} //namespace detail

template<integral T, T N> requires (N >= 0)
using make_integer_sequence = 
    detail::make_seq_helper_t<integral_constant<T, N-1>>;

template<size_t N>
using make_index_sequence = make_integer_sequence<size_t, N>;

} //namespace std

#endif //STD_UTILITY_IMPL_INTEGER_SEQUENCE_HPP
