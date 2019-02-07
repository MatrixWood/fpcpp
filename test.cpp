#include "always.h"
#include "compose.h"
#include "is_callable.h"
#include <iostream>
#include <functional>
#include <string>

namespace compose_test
{
    struct increment
    {
        template <class T>
        constexpr T operator()(T x) const
        {
            return x + 1;
        }
    };

    struct decrement
    {
        template <class T>
        constexpr T operator()(T x) const
        {
            return x - 1;
        }
    };
}

namespace is_callable_test
{
    struct is_callable_class
    {
        void operator()(int) const
        {}
    };
    struct callable_test_param {};
    
    void is_callable_function(int)
    {}
}

int main()
{
    // always test
    static const int ten = 10;
    std::cout << fpcpp::always(ten)(1.2, 2) << std::endl;
    std::cout << fpcpp::always(ten)(false, 2) << std::endl;

    // compose test
    fpcpp::compose(compose_test::increment(), compose_test::decrement(), compose_test::increment())(3);
    
    // is_callable test
    static_assert(fpcpp::is_callable<std::function<void(int)>(int)>::value, "callable");
    static_assert(fpcpp::is_callable<std::function<void(int)>(char)>::value, "callable");
    return 0;
}