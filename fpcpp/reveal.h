#ifndef FPCPP_REVEAL_H
#define FPCPP_REVEAL_H

#include "returns.h"
#include "is_callable.h"

namespace fpcpp
{
    template< template<typename...> class T >
    struct template_holder
    {
        using type = void;
    };
    
    template<typename T, typename = void>
    struct has_failure : fpcpp_false_type
    {};

    template<typename T>
    struct has_failure<T, typename template_holder<
        T::template failure>::type>
        : fpcpp_true_type
    {};

    template<typename T, typename Enable = void>
    struct failure_for
    {};

    template<typename F, typename... Ts>
    struct failure_for<F(Ts...), fpcpp_enable_if_t<has_failure<F>::value>>
    {
        using type = decltype(std::declval<F>()(std::declval<Ts>()...));
    };
}

#endif