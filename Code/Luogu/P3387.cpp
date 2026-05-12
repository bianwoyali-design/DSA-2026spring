#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n{}, m{};
  std::cin >> n >> m;

  std::vector<int> priority(n, 0);
  for (auto &a : priority) {
    std::cin >> a;
  }

  std::vector<int> u(m, 0);
  std::vector<int> v(m, 0);
  std::vector default_g(n, std::vector<int>());
  for (int i = 0; i < m; ++i) {
    std::cin >> u[i] >> v[i];
    default_g[--u[i]].emplace_back(--v[i]);
  }

  std::vector<int> indegree(n, 0);
  auto scc_condensation = [&]() -> std::unordered_map<int, std::vector<int>> {
    int timer = 0;
    std::vector<int> dfn(n, -1);
    std::vector<int> low(n, -1);
    std::vector<int> stack{};
    std::vector<bool> on_stack(n, false);
    std::vector<int> root(n, -1);

    auto dfs = [&](this auto &&self, int u) -> void {
      dfn[u] = timer;
      low[u] = timer;
      ++timer;
      stack.emplace_back(u);
      on_stack[u] = true;

      for (auto v : default_g[u]) {
        if (dfn[v] == -1) {
          self(v);
          low[u] = std::min(low[u], low[v]);
        } else if (on_stack[v]) {
          low[u] = std::min(low[u], dfn[v]);
        }
      }

      if (dfn[u] == low[u]) {
        while (true) {
          int node = stack.back();
          stack.pop_back();
          on_stack[node] = false;
          root[node] = u;
          if (node != u) {
            priority[u] += priority[node];
          } else {
            break;
          }
        }
      }
    };

    for (int i = 0; i < n; ++i) {
      if (dfn[i] == -1) {
        dfs(i);
      }
    }
    std::unordered_map<int, std::vector<int>> new_g;
    for (int i = 0; i < n; ++i) {
      if (root[i] == i) {
        new_g.try_emplace(i);
      }
    }
    for (int i = 0; i < m; ++i) {
      int root_x = root[u[i]], root_y = root[v[i]];
      if (root_x != root_y) {
        new_g[root_x].emplace_back(root_y);
        ++indegree[root_y];
      }
    }

    return new_g;
  };
  auto condensed_g = scc_condensation();

  std::vector<int> dp(n, 0);
  auto topological_sort = [&]() -> int {
    std::queue<int> q;
    for (const auto &[u, _] : condensed_g) {
      if (!indegree[u]) {
        q.emplace(u);
        dp[u] = priority[u];
      }
    }

    while (!q.empty()) {
      auto u = q.front();
      q.pop();
      for (auto v : condensed_g[u]) {
        dp[v] = std::max(dp[v], dp[u] + priority[v]);
        --indegree[v];
        if (!indegree[v]) {
          q.emplace(v);
        }
      }
    }

    int max_res = 0;
    for (auto v : dp) {
      max_res = std::max(max_res, v);
    }
    return max_res;
  };

  std::cout << topological_sort() << '\n';
}
