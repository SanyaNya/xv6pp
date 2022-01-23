#ifndef STD_TYPE_TRAITS_TYPE_IDENTITY_HPP
#define STD_TYPE_TRAITS_TYPE_IDENTITY_HPP

namespace std
{

template<typename T>
struct type_identity
{
    using type = T;
};

} //namespace std

#endif //STD_TYPE_TRAITS_TYPE_IDENTITY_HPP
