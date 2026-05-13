#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n{};
  std::cin >> n;

  std::vector g(n, std::vector<int>());
  std::vector<std::pair<int, int>> edges;
  for (int i = 0; i < n; ++i) {
    int v{};
    while (std::cin >> v && v != 0) {
      --v;
      g[i].emplace_back(v);
      edges.emplace_back(i, v);
    }
  }

  std::vector<int> root(n, -1);
  int scc_count = 0;

  auto tarjan = [&]() -> void {
    int timer = 0;
    std::vector<int> dfn(n, -1);
    std::vector<int> low(n, -1);
    std::vector<int> stack;
    std::vector<bool> on_stack(n, false);

    auto dfs = [&](auto &&self, int u) -> void {
      dfn[u] = low[u] = timer++;
      stack.emplace_back(u);
      on_stack[u] = true;

      for (auto v : g[u]) {
        if (dfn[v] == -1) {
          self(self, v);
          low[u] = std::min(low[u], low[v]);
        } else if (on_stack[v]) {
          low[u] = std::min(low[u], dfn[v]);
        }
      }

      if (dfn[u] == low[u]) {
        ++scc_count;
        while (true) {
          int node = stack.back();
          stack.pop_back();
          on_stack[node] = false;
          root[node] = u;
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

  tarjan();

  std::vector<int> indegree(n, 0);
  std::vector<int> outdegree(n, 0);
  for (const auto &[u, v] : edges) {
    int root_u = root[u];
    int root_v = root[v];
    if (root_u != root_v) {
      ++outdegree[root_u];
      ++indegree[root_v];
    }
  }

  int source_count = 0;
  int sink_count = 0;
  for (int i = 0; i < n; ++i) {
    if (root[i] == i) {
      if (indegree[i] == 0) {
        ++source_count;
      }
      if (outdegree[i] == 0) {
        ++sink_count;
      }
    }
  }

  std::cout << source_count << '\n';
  std::cout << (scc_count == 1 ? 0 : std::max(source_count, sink_count)) << '\n';
}
