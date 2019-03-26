#include "../fpcpp/monoid.h"
#include <iostream>
template <typename T>
T monoidEx(T m1, T m2)
{
  using fpcpp::operator^;
  return m1 ^ m1 ^ m2^ m2;
}

int main()
{
  using fpcpp::sum;

  auto x = monoidEx(sum(1), sum(2));
  std::cout << x << std::endl;
  return 0;
}