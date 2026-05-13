#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n{}, m{};
  std::cin >> n >> m;

  std::vector g(n, std::vector<int>());
  std::vector<int> u(m, 0), v(m, 0);
  for (int i = 0; i < m; ++i) {
    std::cin >> u[i] >> v[i];
    g[--u[i]].emplace_back(--v[i]);
  }

  std::vector<int> root(n, -1);
  std::vector<int> scc_size(n, 0);
  auto scc_condensation = [&]() -> void {
    int timer = 0;
    std::vector<int> dfn(n, -1);
    std::vector<int> low(n, -1);
    std::vector<int> stack;
    std::vector<bool> on_stack(n, false);

    auto dfs = [&](auto &&self, int u) -> void {
      dfn[u] = low[u] = timer++;
      on_stack[u] = true;
      stack.emplace_back(u);

      for (auto v : g[u]) {
        if (dfn[v] == -1) {
          self(self, v);
          low[u] = std::min(low[v], low[u]);
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
          ++scc_size[u];
          if (node == u) {
            break;
          }
        }
      }
    };

    for (int i = 0; i < n; ++i) {
      if (dfn[i] == -1) {
        dfs(dfs, i);
      }
    }
  };

  scc_condensation();

  std::vector<int> outdegree(n, 0);
  for (int i = 0; i < m; ++i) {
    int root_u = root[u[i]], root_v = root[v[i]];
    if (root_u != root_v) {
      ++outdegree[root_u];
    }
  }

  int count = 0;
  int answer = 0;
  for (int i = 0; i < n; ++i) {
    if (root[i] == i && outdegree[i] == 0) {
      ++count;
      answer = scc_size[i];
    }
  }

  std::cout << (count == 1 ? answer : 0) << '\n';
}
