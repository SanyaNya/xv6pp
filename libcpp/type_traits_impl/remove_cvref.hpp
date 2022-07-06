#ifndef STD_TYPE_TRAITS_IMPL_REMOVE_CVREF_HPP
#define STD_TYPE_TRAITS_IMPL_REMOVE_CVREF_HPP

#include "remove_cv.hpp"
#include "remove_reference.hpp"

namespace std
{

template<typename T>
struct remove_cvref : 
    type_identity<
        remove_cv_t<
            remove_reference_t<T>>> {};

template<typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

} //namespace std

#endif //STD_TYPE_TRAITS_IMPL_REMOVE_CVREF_HPP
