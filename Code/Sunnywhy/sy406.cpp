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
  std::vector<int> topo_order;
  auto topo_sort = [&]() -> bool {
    std::queue<int> q;
    for (int u = 0; u < n; ++u) {
      if (!indegree[u]) {
        q.emplace(u);
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

  auto get_critical_activity = [&]() -> std::vector<std::vector<int>> {
    int max_length = *std::max_element(ve.begin(), ve.end());
    std::vector<int> vl(n, max_length);
    std::vector activity(n, std::vector<int>());

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

    return activity;
  };

  auto indegree_copy = indegree;
  std::vector activity(n, std::vector<int>());

  auto print_critical_path = [&](auto &&self, int u,
                                 std::vector<int> &path) -> void {
    path.emplace_back(u);

    if (activity[u].empty()) {
      for (int i = 0; i < path.size(); i++) {
        std::cout << path[i];
        if (i < path.size() - 1) {
          std::cout << "->";
        } else {
          std::cout << '\n';
        }
      }
    } else {
      std::sort(activity[u].begin(), activity[u].end());
      for (auto v : activity[u]) {
        self(self, v, path);
      }
    }

    path.pop_back();
  };

  if (!topo_sort()) {
    std::cout << "No\n";
  } else {
    std::cout << "Yes\n";
    activity = get_critical_activity();
    for (int u = 0; u < n; ++u) {
      if (!indegree_copy[u] && !activity[u].empty()) {
        std::vector<int> path;
        print_critical_path(print_critical_path, u, path);
      }
    }
  }
}
