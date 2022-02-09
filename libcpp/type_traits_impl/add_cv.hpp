#ifndef STD_TYPE_TRAITS_IMPL_ADD_CV_HPP
#define STD_TYPE_TRAITS_IMPL_ADD_CV_HPP

#include "type_identity.hpp"

namespace std
{

template<typename T>
struct add_cv : type_identity<const volatile T> {};

template<typename T>
using add_cv_t = typename add_cv<T>::type;

} //namespace std

#endif //STD_TYPE_TRAITS_IMPL_ADD_CV_HPP
