#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

class DFS {
  int n = 0;
  std::vector<int> status{};
  std::vector<std::vector<int>> g{};

public:
  explicit DFS(const std::vector<std::vector<int>> &g) : n(g.size()), g(g) {
    status.assign(n, 0);
  }

  auto topological_sort() -> std::vector<int> {
    std::vector<int> res;

    auto dfs = [&](auto &&self, int u) -> bool {
      status[u] = 1;

      for (auto v : g[u]) {
        if (status[v] == 0) {
          if (self(self, v)) {
            return true;
          }
        } else if (status[v] == 1) {
          return true;
        }
      }

      res.emplace_back(u);
      status[u] = 2;
      return false;
    };

    for (int i = 0; i < n; ++i) {
      if (!status[i]) {
        if (dfs(dfs, i)) {
          return {};
        }
      }
    }

    std::reverse(res.begin(), res.end());
    return res;
  }
};

class Kahn {
  int n = 0;
  std::vector<std::vector<int>> g{};

public:
  explicit Kahn(const std::vector<std::vector<int>> &g) : n(g.size()), g(g) {}

  auto topological_sort() -> std::vector<int> {
    std::vector<int> indegree(n, 0);
    for (auto &node : g) {
      for (auto v : node) {
        ++indegree[v];
      }
    }

    std::queue<int> q;
    for (int i = 0; i < n; ++i) {
      if (!indegree[i]) {
        q.emplace(i);
      }
    }

    std::vector<int> res;
    while (!q.empty()) {
      auto front = q.front();
      q.pop();
      res.emplace_back(front);

      for (auto v : g[front]) {
        --indegree[v];
        if (!indegree[v]) {
          q.emplace(v);
        }
      }
    }

    return res.size() == n ? res : std::vector<int>{};
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;

  std::vector g(n, std::vector<int>());
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    g[u].emplace_back(v);
  }

  Kahn kahn_sol(g);
  DFS dfs_sol(g);
  std::cout << (kahn_sol.topological_sort() == dfs_sol.topological_sort()) << '\n';
}