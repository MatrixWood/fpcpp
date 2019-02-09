#ifndef FPCPP_MECHANISM_H
#define FPCPP_MECHANISM_H

template<bool STATEMENT, typename T1, typename T2>
struct typeif
{
    using type = T1;
};

template<typename T1, typename T2>
struct typeif<false, T1, T2>
{
    using type = T2;
};

template<typename T>
struct instance_of
{
    using type = T;
    instance_of(int = 0) {}
};

template<bool T>
struct selector
{
};

template<typename T1, typename T2>
struct OR
{
    static const bool value = (T1::value || T2::value);
};

template<typename T1, typename T2>
struct AND
{
    static const bool value = (T1::value && T2::value);
};

template<bool B, typename T2>
struct static_OR_helper;

template<typename T2>
struct static_OR_helper<false, T2> : selector<T2::value>
{
};

template<typename T2>
struct static_OR_helper<true, T2> : selector<true>
{
};

template<typename T1, typename T2>
struct static_OR : static_OR_helper<T1::value, T2>
{
};

template<typename T>
struct is_const : selector<false>
{
};

template<typename T>
struct is_const<const T> : selector<true>
{
};

template<typename T>
struct add_reference
{
    using type = T&;
};

template<typename T>
struct add_reference<T&>
{
    using type = T&;
};

template<>
struct add_reference<void>
{
};

/*
struct ERROR_UNDEFINED_TYPE;

template<size_t N, typename CONTAINER, typename ERR = ERROR_UNDEFINED_TYPE>
struct typeat;
*/



#endif