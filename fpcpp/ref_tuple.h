#ifndef FPCPP_REF_TUPLE_H
#define FPCPP_REF_TUPLE_H

#include <tuple>

namespace fpcpp
{
    template<typename T>
    struct remove_rvalue_reference
    {
        using type = T;
    };

    template<typename T>
    struct remove_rvalue_reference<T&&>
    {
        using type = T;
    };

    template<typename T>
    using remove_rvalue_reference_t = typename remove_rvalue_reference<T>::type;

    template<typename... Ts>
    constexpr auto make_ref_tuple(Ts&&... x)
    {
        return std::tuple<remove_rvalue_reference_t<Ts>...>(std::forward<Ts>(x)...);
    }
}
#endif