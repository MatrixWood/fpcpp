#include "always.h"
#include "compose.h"
#include <iostream>

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

int main()
{
    // always test
    static const int ten = 10;
    std::cout << fpcpp::always(ten)(1.2, 2) << std::endl;
    std::cout << fpcpp::always(ten)(false, 2) << std::endl;

    // compose test
    fpcpp::compose(compose_test::increment(), compose_test::decrement(), compose_test::increment())(3);
    return 0;
}