#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n = 0, t = 0;
  std::cin >> n >> t;
  std::vector g(n + 1, std::vector<int>());
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  int p, q;
  long long v1, v2;
  std::cin >> p >> q >> v1 >> v2;

  int log = 1;
  while ((1 << log) <= n) {
    ++log;
  }

  std::vector<int> depth(n + 1, 0);
  std::vector up(n + 1, std::vector<int>(log, -1));

  auto dfs = [&](auto &&self, int u, int parent) -> void {
    up[u][0] = parent;
    for (int j = 1; j < log; ++j) {
      if (up[u][j - 1] != -1) {
        up[u][j] = up[up[u][j - 1]][j - 1];
      }
    }

    for (int v : g[u]) {
      if (v == parent) {
        continue;
      }
      depth[v] = depth[u] + 1;
      self(self, v, u);
    }
  };

  dfs(dfs, t, -1);

  auto lca = [&](int u, int v) -> int {
    if (depth[v] > depth[u]) {
      std::swap(u, v);
    }

    for (int j = log - 1; j >= 0; --j) {
      if (up[u][j] != -1 && depth[up[u][j]] >= depth[v]) {
        u = up[u][j];
      }
    }

    if (u == v) {
      return u;
    }

    for (int j = log - 1; j >= 0; --j) {
      if (up[u][j] != -1 && up[u][j] != up[v][j]) {
        u = up[u][j];
        v = up[v][j];
      }
    }

    return up[u][0];
  };

  auto jump = [&](int u, long long steps) -> int {
    for (int j = 0; steps > 0; ++j) {
      if (steps & 1) {
        u = up[u][j];
      }
      steps >>= 1;
    }
    return u;
  };

  const int root = lca(p, q);
  const long long distance = depth[p] + depth[q] - 2LL * depth[root];
  const long long days = distance / (v1 + v2);
  const long long from_p = days * v1;

  int station = 0;
  if (from_p <= depth[p] - depth[root]) {
    station = jump(p, from_p);
  } else {
    station = jump(q, distance - from_p);
  }

  std::cout << days << ' ' << depth[station] << '\n';
}
