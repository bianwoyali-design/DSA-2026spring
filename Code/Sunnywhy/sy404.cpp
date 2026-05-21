#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n{}, m{};
  std::cin >> n >> m;
  std::vector g(n, std::vector<std::pair<int, int>>());
  std::vector<int> indegree(n, 0);
  for (int i = 0; i < m; ++i) {
    int u{}, v{}, w{};
    std::cin >> u >> v >> w;
    g[u].emplace_back(v, w);
    ++indegree[v];
  }

  std::vector<int> ve(n, 0);
  auto topo_sort = [&]() -> bool {
    std::queue<int> q;
    std::vector<int> topo_order;
    for (int i = 0; i < n; ++i) {
      if (!indegree[i]) {
        q.emplace(i);
      }
    }

    while (!q.empty()) {
      int u = q.front();
      q.pop();
      topo_order.emplace_back(u);

      for (auto &&[v, w] : g[u]) {
        if (ve[u] + w > ve[v]) {
          ve[v] = ve[u] + w;
        }

        --indegree[v];
        if (!indegree[v]) {
          q.emplace(v);
        }
      }
    }

    if (topo_order.size() == n) {
      return true;
    } else {
      return false;
    }
  };

  if (topo_sort()) {
    std::cout << "Yes\n";
    int max_length = *std::max_element(ve.begin(), ve.end());
    std::cout << max_length << '\n';
  } else {
    std::cout << "No\n";
  }
}