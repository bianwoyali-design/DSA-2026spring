#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;
  std::vector<int> r(n);
  for (auto &v : r) {
    std::cin >> v;
  }

  std::vector<int> indegree(n, 0);
  std::vector adj(n, std::vector<int>());
  std::vector dp(n, std::vector<int>(2, 0));
  for (int i = 0; i + 1 < n; ++i) {
    int l, k;
    std::cin >> l >> k;
    adj[--k].emplace_back(--l);
    ++indegree[l];
  }

  int root = std::ranges::find(indegree, 0) - indegree.begin();
  auto dfs = [&](this auto &&self, int node) -> void {
    if (adj[node].empty()) {
      dp[node][0] = 0;
      dp[node][1] = r[node];
      return;
    }

    dp[node][1] = r[node];
    for (auto v : adj[node]) {
      self(v);
      dp[node][0] += std::max(dp[v][1], dp[v][0]);
      dp[node][1] += dp[v][0];
    }
  };

  dfs(root);

  std::cout << std::max(dp[root][0], dp[root][1]) << '\n';
}