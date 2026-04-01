#include <iostream>
#include <vector>
#include <algorithm>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;
  std::vector<int> h(n);
  for (auto &v : h)
    std::cin >> v;

  std::vector<int> st_max;
  std::vector<int> st_min;

  int ans = 0;
  for (int j = 0; j < n; ++j) {
    while (!st_max.empty() && h[st_max.back()] < h[j])
      st_max.pop_back();

    int left_border = st_max.empty() ? -1 : st_max.back();

    while (!st_min.empty() && h[st_min.back()] >= h[j])
      st_min.pop_back();

    if (!st_min.empty()) {
      auto it = std::upper_bound(st_min.begin(), st_min.end(), left_border);
      if (it != st_min.end()) {
        int min_l = *it;
        ans = std::max(ans, j - min_l + 1);
      }
    }

    st_max.emplace_back(j);
    st_min.emplace_back(j);
  }

  std::cout << ans << '\n';
}