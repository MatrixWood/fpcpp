#ifndef FPCPP_MONOID_H
#define FPCPP_MONOID_H

#include <type_traits>
#include <tuple>

namespace fpcpp
{
template <typename M>
struct monoid
{
  static M mempty();
};

template <typename N>
struct sum_monoid
{
  sum_monoid() = default;

  constexpr sum_monoid(N num) noexcept : n(num) {}

  constexpr sum_monoid(const sum_monoid &m) noexcept : n(m.n) {}

  constexpr sum_monoid(sum_monoid &&m) noexcept : n(std::move(m.n)) {}

  ~sum_monoid() = default;

  constexpr operator N() const noexcept
  {
    return n;
  }

  const sum_monoid &operator=(const sum_monoid &m) noexcept
  {
    n = m.n;
    return *this;
  }

  const sum_monoid &operator=(sum_monoid &&m) noexcept
  {
    n = std::move(m.n);
    return *this;
  }

  constexpr sum_monoid operator+(const sum_monoid &n2) const noexcept
  {
    return sum_monoid(n + n2.n);
  }

  N n;
};

template <typename N>
constexpr sum_monoid<N> sum(N num) noexcept
{
  return sum_monoid<N>(num);
}

template <typename N>
struct monoid<sum_monoid<N>>
{
  static constexpr sum_monoid<N> mempty() noexcept
  {
    return sum(N(0));
  }
};

template <typename N>
constexpr sum_monoid<N> mappend(const sum_monoid<N> &n1,
                                const sum_monoid<N> &n2)
{
  return n1 + n2;
}

template <typename N>
constexpr sum_monoid<N> operator^(const sum_monoid<N> &n1,
                                  const sum_monoid<N> &n2)
{
  return mappend(n1, n2);
}

template <typename...Ts>
struct monoid<std::tuple<Ts...>>
{
  static std::tuple<Ts...> id()
  {
    return std::make_tuple(monoid<Ts>::id()...);
  }
};

namespace
{
  template <std::size_t N, typename T>
  struct tupMappend
  {
    static void apply(T& ret, const T& t2)
    {
      tupMappend<N-1, T>::apply(ret, t2);
      std::get<N>(ret) = std::get<N>(ret) ^ std::get<N>(t2);
    }
  };

  template <typename T>
  struct tupMappend<0, T>
  {
    static void apply(T& ret, const T& t2)
    {
      std::get<0>(ret) = std::get<0>(ret) ^ std::get<0>(t2);
    }
  };
}


template <typename...Ts>
std::tuple<Ts...> mappend(const std::tuple<Ts...>& t1,
                          const std::tuple<Ts...>& t2)
{
  auto ret = t1;
  tupMappend<sizeof...(Ts)-1, std::tuple<Ts...>>::apply(ret, t2);
  return ret;
}

template <typename...Ts>
std::tuple<Ts...> operator^ (const std::tuple<Ts...>& t1,
                             const std::tuple<Ts...>& t2)
{
  return mappend(t1, t2);
}
} // namespace fpcpp

#endif