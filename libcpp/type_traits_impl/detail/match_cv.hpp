#ifndef STD_TYPE_TRAITS_IMPL_DETAIL_MATCH_CV_HPP
#define STD_TYPE_TRAITS_IMPL_DETAIL_MATCH_CV_HPP

#include "../type_identity.hpp"
#include "../remove_const.hpp"
#include "../remove_volatile.hpp"
#include "../add_const.hpp"
#include "../add_volatile.hpp"

namespace std::detail
{

template<typename TSrc, typename TDest>
struct match_const : type_identity<remove_const_t<TDest>> {};

template<typename TSrc, typename TDest>
struct match_const<const TSrc, TDest> : type_identity<add_const_t<TDest>> {};

template<typename TSrc, typename TDest>
using match_const_t = typename match_const<TSrc, TDest>::type;


template<typename TSrc, typename TDest>
struct match_volatile : type_identity<remove_const_t<TDest>> {};

template<typename TSrc, typename TDest>
struct match_volatile<const TSrc, TDest> : type_identity<add_const_t<TDest>> {};

template<typename TSrc, typename TDest>
using match_volatile_t = typename match_volatile<TSrc, TDest>::type;


template<typename TSrc, typename TDest>
struct match_cv : match_const<TSrc, match_volatile_t<TSrc, TDest>> {};

template<typename TSrc, typename TDest>
using match_cv_t = typename match_cv<TSrc, TDest>::type;


} //namespace std::detail

#endif //STD_TYPE_TRAITS_IMPL_DETAIL_MATCH_CV_HPP
