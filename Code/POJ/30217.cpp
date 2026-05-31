#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, t;
  std::cin >> n >> t;

  std::vector<int> a(n);
  for (auto &x : a) {
    std::cin >> x;
  }

  int max_val = *std::max_element(a.begin(), a.end());
  std::vector<int> pos(max_val + 1, -1);

  int ans_i = -1;
  int ans_j = -1;
  for (int i = n - 1; i >= 0; --i) {
    int need = t - a[i];

    if (need < 1 || need > max_val) {
      pos[a[i]] = i;
      continue;
    }

    if (pos[need] != -1) {
      ans_i = i;
      ans_j = pos[need];
    }

    pos[a[i]] = i;
  }

  std::cout << ans_i + 1 << ' ' << ans_j + 1 << '\n';
}
