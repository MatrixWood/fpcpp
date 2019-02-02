#ifndef CPP_RETURNS_H
#define CPP_RETURNS_H

#include <utility>

#define FPCPP_RETURNS(...) -> decltype(__VA_ARGS__) \
                            { \
                                return __VA_ARGS__; \
                            } \
                            static_assert(true, "")

#define FPCPP_AUTO_FORWARD(x) std::forward<decltype(x)>(x)

#endif