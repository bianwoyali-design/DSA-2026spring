#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;
  std::vector<int> time(n, 0);
  for (auto &&t : time) {
    std::cin >> t;
  }

  std::vector edges(n, std::vector<int>());
  std::vector<int> indegree(n, 0);
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    edges[--u].emplace_back(--v);
    ++indegree[v];
  }

  int count = 0;
  std::queue<int> q;
  std::vector<int> dp(n, 0);

  for (int i = 0; i < n; ++i) {
    if (!indegree[i]) {
      dp[i] = time[i];
      q.emplace(i);
    }
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    ++count;

    for (auto v : edges[u]) {
      dp[v] = std::max(dp[v], dp[u] + time[v]);
      if (!--indegree[v]) {
        q.emplace(v);
      }
    }
  }

  if (count != n) {
    std::cout << -1 << '\n';
    return 0;
  }

  std::cout << *std::max_element(dp.begin(), dp.end()) << '\n';
}