#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

class DisjSet {
private:
  std::vector<int> parent;
  std::vector<int> rank;

public:
  explicit DisjSet(int n) : parent(n), rank(n, 0) {
    std::ranges::iota(parent, 0);
  }

  auto find(int x) -> int {
    return parent[x] == x ? x : parent[x] = find(parent[x]);
  }

  auto unite(int x, int y) -> bool {
    int root_x = find(x);
    int root_y = find(y);
    if (root_x == root_y) {
      return false;
    }

    if (rank[root_x] < rank[root_y]) {
      parent[root_x] = root_y;
    } else if (rank[root_x] > rank[root_y]) {
      parent[root_y] = root_x;
    } else {
      parent[root_y] = root_x;
      ++rank[root_x];
    }
    return true;
  }
};

struct Edge {
  int u, v;
  int weight;
  auto operator<(const Edge &other) const -> bool {
    return weight > other.weight;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;
  std::vector<Edge> edges;
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    edges.emplace_back(Edge{u, v, w});
  }

  DisjSet dsu(n + 1);
  std::sort(edges.begin(), edges.end());

  std::vector g(n + 1, std::vector<std::pair<int, int>>());
  int count = 0;
  for (auto [u, v, w] : edges) {
    if (dsu.unite(u, v)) {
      g[u].emplace_back(v, w);
      g[v].emplace_back(u, w);
      if (++count == n - 1) {
        break;
      }
    }
  }

  int LOG = 1;
  while ((1 << LOG) <= n)
    ++LOG;

  constexpr static int INF = 1e9;
  std::vector<int> depth(n + 1, 0);
  std::vector up(n + 1, std::vector<int>(LOG, 0));
  std::vector min_weight(n + 1, std::vector<int>(LOG, INF));
  std::vector<bool> visited(n + 1, false);

  auto dfs = [&](this auto &&self, int u, int parent) -> void {
    up[u][0] = parent;
    visited[u] = true;
    for (int k = 1; k < LOG; ++k) {
      up[u][k] = up[up[u][k - 1]][k - 1];
      min_weight[u][k] =
          std::min(min_weight[u][k - 1], min_weight[up[u][k - 1]][k - 1]);
    }

    for (auto &&[v, w] : g[u]) {
      if (v == parent) {
        continue;
      }
      depth[v] = depth[u] + 1;
      min_weight[v][0] = w;
      self(v, u);
    }
  };

  auto lift = [&](int &u, int step) -> int {
    int ans = INF;
    for (int k = 0; k < LOG; ++k) {
      if ((step >> k) & 1) {
        ans = std::min(ans, min_weight[u][k]);
        u = up[u][k];
      }
    }
    return ans;
  };

  auto lca = [&](int u, int v) -> int {
    if (dsu.find(u) != dsu.find(v)) {
      return -1;
    }

    if (depth[u] < depth[v]) {
      std::swap(u, v);
    }
    int ans = std::min(INF, lift(u, depth[u] - depth[v]));
    if (u == v) {
      return ans;
    }

    for (int k = LOG - 1; k >= 0; --k) {
      if (up[u][k] != up[v][k]) {
        ans = std::min({ans, min_weight[u][k], min_weight[v][k]});
        u = up[u][k];
        v = up[v][k];
      }
    }
    ans = std::min({ans, min_weight[u][0], min_weight[v][0]});
    return ans;
  };

  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      dfs(i, 0);
    }
  }

  int q;
  std::cin >> q;
  while (q--) {
    int src, tgt;
    std::cin >> src >> tgt;
    std::cout << lca(src, tgt) << '\n';
  }
}
