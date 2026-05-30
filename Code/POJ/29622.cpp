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
    std::iota(parent.begin(), parent.end(), 0);
  }

  auto find(int x) -> int { return parent[x] == x ? x : find(parent[x]); }

  auto unite(int x, int y) -> bool {
    int root_x = find(x);
    int root_y = find(y);

    if (root_x == root_y) {
      return false;
    }

    if (rank[root_x] > rank[root_y]) {
      parent[root_y] = root_x;
    } else if (rank[root_x] < rank[root_y]) {
      parent[root_x] = root_y;
    } else {
      parent[root_y] = root_x;
      ++rank[root_x];
    }
    return true;
  }
};

struct Edge {
  int u, v, w;
  auto operator<(const Edge &other) const -> bool { return w < other.w; }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;

  std::vector<Edge> edges(n);
  DisjSet dsu(n);
  while (m--) {
    int u, v, w;
    std::cin >> u >> v >> w;
    edges.emplace_back(Edge{--u, --v, w});
  }

  std::sort(edges.begin(), edges.end());

  int mst = 0;
  int count = 0;
  for (auto [u, v, w] : edges) {
    if (dsu.unite(u, v)) {
      mst += w;
      if (++count == n - 1) {
        break;
      }
    }
  }

  if (count != n - 1) {
    std::cout << "orz\n";
  } else {
    std::cout << mst << '\n';
  }
}