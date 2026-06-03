#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, k;
  std::cin >> n >> k;
  std::vector<int> dp(k, -1);
  dp[0] = 0;
  for (int i = 0; i < n; ++i) {
    int candy;
    std::cin >> candy;

    auto prev = dp;
    for (int r = 0; r < k; ++r) {
      if (prev[r] == -1) {
        continue;
      }

      int newr = (r + candy) % k;
      dp[newr] = std::max(dp[newr], prev[r] + candy);
    }
  }

  std::cout << dp[0] << '\n';
}