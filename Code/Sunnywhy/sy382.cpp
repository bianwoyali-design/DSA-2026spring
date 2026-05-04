#include <iostream>
#include <vector>

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

  std::vector<bool> visited(n, false);
  std::vector<bool> stack(n, false);

  auto dfs = [&](auto &&self, int node) -> bool {
    visited[node] = true;
    stack[node] = true;

    for (auto &&v : g[node]) {
      if (!visited[v] && self(self, v)) {
        return true;
      } else if (stack[v]) {
        return true;
      }
    }

    stack[node] = false;
    return false;
  };

  bool flag = false;
  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      flag = dfs(dfs, i);
      if (flag) {
        break;
      }
    }
  }

  if (flag) {
    std::cout << "Yes\n";
  } else {
    std::cout << "No\n";
  }
}