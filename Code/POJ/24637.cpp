#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n{};
  std::cin >> n;
  std::vector<int> tree(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    std::cin >> tree[i];
  }

  std::vector dp(2 * n + 2, std::vector<int>(2, 0));
  auto dfs = [&](auto &&self, int i) -> void {
    if (i > n) {
      return;
    }

    int left = i << 1;
    int right = i << 1 | 1;

    self(self, left);
    self(self, right);

    dp[i][0] = std::max(dp[left][1], dp[left][0]) +
               std::max(dp[right][1], dp[right][0]);
    dp[i][1] = dp[left][0] + dp[right][0] + tree[i];
  };

  dfs(dfs, 1);

  std::cout << std::max(dp[1][0], dp[1][1]) << '\n';
}