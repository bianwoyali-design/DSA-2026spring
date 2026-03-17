#include <iostream>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;
  if (n == 0) {
    std::cout << 1 << '\n';
    return 0;
  }

  int w = 32 - __builtin_clz(n);
  int MASK = (1 << w) - 1;
  std::cout << (n ^ MASK) << '\n';
  return 0;
}