#ifndef FPCPP_ALWAYS_H
#define FPCPP_ALWAYS_H

namespace fpcpp
{
    template<typename T>
    struct always_base
    {
        T x;

        constexpr always_base() {}

        constexpr always_base(T x) : x(x) {}

        template<typename... As>
        constexpr T operator()(As&&...) const
        {
            return this->x;
        }
    };

    template<typename T>
    constexpr always_base<T> always(T x)
    {
        return always_base<T>(x);
    }

    template<typename T>
    constexpr always_base<T&> always_ref(T& x)
    {
        return always_base<T&>(x);
    }
}

#endif