#include <iostream>
#include <queue>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;

  std::vector<long long> c(n);
  std::vector<int> u(n);
  std::vector<int> indegree(n, 0);
  std::vector<int> outdegree(n, 0);
  std::vector weight(n, std::vector<int>(m, 0));
  std::vector g(n, std::vector<int>());

  for (int i = 0; i < n; ++i) {
    std::cin >> c[i] >> u[i];
  }

  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    --u, --v;

    if (weight[u][v] == 0) {
      g[u].emplace_back(v);
      ++indegree[v];
      ++outdegree[u];
    }

    weight[u][v] += w;
  }

  auto indegree_cpy = indegree;
  std::queue<int> q;
  for (int i = 0; i < n; ++i) {
    if (!indegree[i]) {
      q.emplace(i);
    }
  }

  std::vector<int> topo_order;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    topo_order.emplace_back(u);

    for (auto v : g[u]) {
      --indegree[v];
      if (!indegree[v]) {
        q.emplace(v);
      }
    }
  }

  if (topo_order.size() != n) {
    std::cout << "NULL\n";
    return 0;
  }

  for (int i = 0; i < n; ++i) {
    if (indegree_cpy[i]) {
      c[i] -= u[i];
    }
  }

  for (auto u : topo_order) {
    if (c[u] > 0) {
      for (auto v : g[u]) {
        c[v] += c[u] * weight[u][v];
      }
    }
  }

  std::vector<int> res;
  for (int i = 0; i < n; ++i) {
    if (c[i] > 0 && !outdegree[i]) {
      res.emplace_back(i);
    }
  }

  if (res.empty()) {
    std::cout << "NULL\n";
  } else {
    for (auto i : res) {
      std::cout << i + 1 << ' ' << c[i] << '\n';
    }
  }
}