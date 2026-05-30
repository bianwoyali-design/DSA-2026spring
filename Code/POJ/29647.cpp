#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;
  std::vector<int> r(n);
  for (auto &x : r) {
    std::cin >> x;
  }

  std::vector g(n, std::vector<int>());
  std::vector<int> indegree(n, 0);
  for (int i = 0; i + 1 < n; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    g[v].emplace_back(u);
    ++indegree[u];
  }

  int root = std::ranges::find(indegree, 0) - indegree.begin();

  std::vector dp(n, std::vector<int>(2, 0));
  for (int i = 0; i < n; ++i) {
    dp[i][1] = r[i];
  }

  auto dfs = [&](auto &&self, int u) -> void {
    if (g[u].empty()) {
      return;
    }

    for (auto v : g[u]) {
      self(self, v);
      dp[u][0] += std::max(dp[v][0], dp[v][1]);
      dp[u][1] += dp[v][0];
    }
  };

  dfs(dfs, root);
  std::cout << std::max(dp[root][0], dp[root][1]) << '\n';
}