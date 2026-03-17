#include <array>
#include <iostream>

auto main() -> int {
  int n;
  std::array<int, 31> T = {0, 1, 1};
  std::cin >> n;
  if (n >= 1 && n <= 2) {
    std::cout << T[n] << "\n";
    return 0;
  }
  for (int i = 3; i <= n; i++) {
    T[i] = T[i - 1] + T[i - 2] + T[i - 3];
  }
  std::cout << T[n] << "\n";
  return 0;
}