#ifndef STD_TYPE_TRAITS_HPP
#define STD_TYPE_TRAITS_HPP

namespace std
{

template<typename T, T v>
struct integral_constant
{
    using value_type = T;
    using type = integral_constant;

    static constexpr T value = v;
    
    constexpr operator value_type() const noexcept
    {
        return value;
    }

    constexpr value_type operator()() const noexcept
    {
        return value;
    }
};

template<bool B>
using bool_constant = integral_constant<bool, B>;

using false_type = bool_constant<false>;
using true_type  = bool_constant<true>;


template<typename T>
struct is_trivially_copyable
    : bool_constant<__is_trivially_copyable(T)> {};

template<typename T>
inline constexpr bool is_trivially_copyable_v =
    is_trivially_copyable<T>::value;


template<typename T>
struct is_trivially_default_constructible
    : bool_constant<__is_trivially_constructible(T)> {};

template<typename T>
inline constexpr bool is_trivially_default_constructible_v =
    is_trivially_default_constructible<T>::value;


template<typename T>
struct is_trivial
    : bool_constant<
        is_trivially_copyable<T>::value && 
        is_trivially_default_constructible<T>::value> {};

template<typename T>
inline constexpr bool is_trivial_v = is_trivial<T>::value;


template<typename T>
struct is_enum : bool_constant<__is_enum(T)> {};

template<typename T>
inline constexpr bool is_enum_v = is_enum<T>::value;


template<typename T>
struct type_identity
{
    using type = T;
};


template<typename E> requires is_enum_v<E>
struct underlying_type : type_identity<__underlying_type(E)> {};

template<typename E> requires is_enum_v<E>
using underlying_type_t = typename underlying_type<E>::type;

template<typename E> requires is_enum_v<E>
constexpr auto to_underlying(E e) noexcept
{
    return static_cast<underlying_type_t<E>>(e);
}

} //namespace std

#endif //STD_TYPE_TRAITS_HPP
