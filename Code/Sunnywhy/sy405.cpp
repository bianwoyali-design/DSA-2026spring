#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <queue>

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
  std::vector<int> topo_order;
  auto topo_sort = [&]() -> bool {
    std::queue<int> q;
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

    return topo_order.size() == n;
  };

  std::vector activity(n, std::vector<int>());
  auto get_critical_activity = [&]() -> int {
    int max_length = *std::max_element(ve.begin(), ve.end());
    std::vector<int> vl(n, max_length);

    std::reverse(topo_order.begin(), topo_order.end());

    for (auto u : topo_order) {
      for (auto &&[v, w] : g[u]) {
        if (vl[v] - w < vl[u]) {
          vl[u] = vl[v] - w;
        }
      }
    }

    for (int u = 0; u < n; ++u) {
      for (auto &&[v, w] : g[u]) {
        int e = ve[u];
        int l = vl[v] - w;
        if (e == l) {
          activity[u].emplace_back(v);
        }
      }
    }

    return max_length;
  };

  if (!topo_sort()) {
    std::cout << "No\n";
  } else {
    std::cout << "Yes\n";
    get_critical_activity();
    for (int u = 0; u < n; ++u) {
      if (!activity[u].empty()) {
        std::sort(activity[u].begin(), activity[u].end());
        for (auto v : activity[u]) {
          std::cout << u << ' ' << v << '\n';
        }
      }
    }
  }
}