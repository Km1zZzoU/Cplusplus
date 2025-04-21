#include <iostream>

#include <type_traits>

template <int N, int M = 2>
struct isprime : std::bool_constant<N % M != 0 && isprime<N, M + 1>::value> {};

template <int N>
struct isprime<N, N> : std::true_type {};

template <int N>
struct nextprime : std::conditional_t<isprime<N>::value, std::integral_constant<int, N>, nextprime<N + 1>> {};

template <int N>
struct prime : nextprime<prime<N - 1>::value + 1> {};

template <>
struct prime<1> : std::integral_constant<int, 2> {};

int main() {
  std::cout << prime<1>::value << "\n";
  std::cout << prime<5>::value << "\n";
}
