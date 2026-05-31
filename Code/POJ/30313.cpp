#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <set>
#include <tuple>
#include <unordered_set>
#include <vector>

class DisjSet {
private:
  std::vector<int> parent;
  std::vector<int> rank;

public:
  explicit DisjSet(int n) : parent(n), rank(n, 0) {
    std::iota(parent.begin(), parent.end(), 0);
  }

  auto find(int x) -> int { return parent[x] == x ? x : find(parent[x]); }

  auto unite(int x, int y) -> bool {
    int root_x = find(x);
    int root_y = find(y);

    if (root_x == root_y) {
      return false;
    }

    if (rank[root_y] > rank[root_x]) {
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

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;

  std::vector adj(n, std::unordered_set<int>());
  std::vector<std::tuple<int, int, int>> edges;
  std::vector<int> comp(n, -1);

  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    --u, --v;
    edges.emplace_back(w, u, v);
    adj[u].insert(v);
    adj[v].insert(u);
  }

  std::set<int> unvisited;
  for (int i = 0; i < n; ++i) {
    unvisited.insert(i);
  }

  int component_count = 0;
  std::queue<int> q;
  while (!unvisited.empty()) {
    int start = *unvisited.begin();
    unvisited.erase(start);
    q.emplace(start);
    comp[start] = component_count;

    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto it = unvisited.begin(); it != unvisited.end();) {
        int v = *it;
        if (!adj[u].count(v)) {
          it = unvisited.erase(it);
          comp[v] = component_count;
          q.emplace(v);
        } else {
          ++it;
        }
      }
    }

    ++component_count;
  }

  DisjSet dsu(component_count);
  std::sort(edges.begin(), edges.end());
  int mst = 0;
  int count = 0;
  for (auto [w, u, v] : edges) {
    int cu = comp[u], cv = comp[v];
    if (cu == cv) {
      continue;
    }

    if (dsu.unite(cu, cv)) {
      mst += w;
      if (++count == n - 1) {
        break;
      }
    }
  }

  std::cout << mst << '\n';
}