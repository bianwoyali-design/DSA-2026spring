#include <iostream>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;
  int c_prev = 1;
  int c_curr = 1;
  for (int i = 1; i <= n; ++i) {
    c_prev = c_curr;
    c_curr = (4 * i - 2) * c_prev / (i + 1);
  }
  std::cout << c_curr << '\n';
}