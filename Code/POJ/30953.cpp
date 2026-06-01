#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;
  std::vector reverse_g(n, std::vector<int>());
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    reverse_g[v].emplace_back(u);
  }

  std::vector<int> dp(n, -1);

  for (int i = 0; i < n; ++i) {
    if (dp[i] != -1) {
      continue;
    }

    std::queue<int> q;
    q.emplace(i);
    dp[i] = i;

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      for (auto v : reverse_g[u]) {
        if (dp[v] == -1) {
          dp[v] = i;
          q.emplace(v);
        }
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    std::cout << dp[i] + 1 << " \n"[i + 1 == n];
  }
}