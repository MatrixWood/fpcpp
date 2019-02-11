#ifndef FPCPP_TRAITS_H
#define FPCPP_TRAITS_H

namespace fpcpp
{
    template<typename Tp, Tp Val>
    struct fpcpp_integral_constant
    {
        static constexpr Tp value = Val;
        using value_type = Tp;
        using type = fpcpp_integral_constant<Tp, Val>;
        constexpr operator value_type() const noexcept
        {
            return value;
        }
        constexpr value_type operator()() const noexcept
        {
            return value;
        }
    };

    template<bool Val>
    using fpcpp_bool_constant = fpcpp_integral_constant<bool, Val>;

    using fpcpp_true_type = fpcpp_bool_constant<true>;
    using fpcpp_false_type = fpcpp_bool_constant<false>;

    template<bool T, typename = void>
    struct fpcpp_enable_if
    {};

    template<typename T>
    struct fpcpp_enable_if<true, T>
    {
        using type = T;
    };

    
    template<bool T, typename Ty = void>
	using fpcpp_enable_if_t = typename fpcpp_enable_if<T, Ty>::type;
}

#endif