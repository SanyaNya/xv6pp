#pragma once

namespace std
{

template<typename T>
struct type_identity
{
    using type = T;
};

} //namespace std
