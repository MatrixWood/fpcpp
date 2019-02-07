#ifndef FPCPP_IS_CALLABLE_H
#define FPCPP_IS_CALLABLE_H

#include <utility>
#include "traits.h"

namespace fpcpp
{
    template<typename T>
    struct holder
    {
        using type = void;
    };

    template<typename F, typename = void>
    struct is_callable : fpcpp_false_type
    {};

    template<typename F, typename... Args>
    struct is_callable<F(Args...), typename holder<
        decltype( std::declval<F>()(std::declval<Args>()...) )>::type>
        : fpcpp_true_type
    {};
}

#endif