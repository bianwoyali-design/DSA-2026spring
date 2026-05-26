#include <iostream>
#include <queue>
#include <vector>

auto kahn(int n, const std::vector<std::vector<int>> &adj,
          std::vector<int> &indegree) -> bool {
  std::queue<int> q;
  for (int u = 0; u < n; ++u) {
    if (!indegree[u]) {
      q.emplace(u);
    }
  }

  std::vector<int> order;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    order.emplace_back(u);

    for (auto v : adj[u]) {
      --indegree[v];
      if (!indegree[v]) {
        q.emplace(v);
      }
    }
  }

  return order.size() != n;
}

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t{};
  std::cin >> t;
  while (t--) {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> indegree(n, 0);
    std::vector adj(n, std::vector<int>());
    for (int i = 0; i < m; ++i) {
      int u, v;
      std::cin >> u >> v;
      adj[--u].emplace_back(--v);
      ++indegree[v];
    }

    std::cout << (kahn(n, adj, indegree) ? "Yes\n" : "No\n");
  }
}