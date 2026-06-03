#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;
  std::vector<int> x(n);
  for (auto &a : x) {
    std::cin >> a;
  }

  std::sort(x.rbegin(), x.rend());

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (x[i] >= i + 1) {
      ans = i + 1;
    } else {
      break;
    }
  }

  std::cout << ans << '\n';
}