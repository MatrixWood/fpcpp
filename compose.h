#ifndef FPCPP_COMPOSE_H
#define FPCPP_COMPOSE_H

#include "returns.h"
#include "always.h"
#include <tuple>

namespace fpcpp
{
    template<typename F1, typename F2>
    struct compose_kernel
    {
        F1 f1;
        F2 f2;
        constexpr compose_kernel() {}

        template<typename A, typename B>
        constexpr compose_kernel(A f1, B f2) : f1(f1), f2(f2) {}

        template<typename... Ts>
        constexpr auto operator()(Ts&&... xs) const FPCPP_RETURNS
        (
            this->f1(this->f2(std::forward<Ts>(xs)...))
        );
    };

    template<typename F, typename... Fs>
    struct compose_adaptor : compose_kernel<F, compose_adaptor<Fs...>>
    {
        using tail = compose_adaptor<Fs...>;
        using base = compose_kernel<F, tail>;

        constexpr compose_adaptor() {}

        template<typename X, typename... Xs>
        constexpr compose_adaptor(X f1, Xs... fs) : base(f1, tail(fs...)) {}
    };

    template<typename F>
    struct compose_adaptor<F> : F
    {
        constexpr compose_adaptor() {}

        template<typename X>
        constexpr compose_adaptor(X f1) : F(f1) {}
    };

    template<typename... Fs>
    constexpr compose_adaptor<Fs...> compose(Fs... fs)
    {
        return compose_adaptor<Fs...>(fs...);
    }
}

#endif