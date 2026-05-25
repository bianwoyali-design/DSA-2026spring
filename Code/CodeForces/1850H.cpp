#include <iostream>
#include <numeric>
#include <vector>

class DisjSet {
private:
  std::vector<int> parent;
  std::vector<long long> dist;

public:
  explicit DisjSet(int n) : parent(n), dist(n, 0) {
    std::ranges::iota(parent, 0);
  }

  auto find(int x) -> int {
    if (parent[x] == x) {
      return x;
    }
    int old_parent = parent[x];
    parent[x] = find(old_parent);
    dist[x] = dist[x] + dist[old_parent];
    return parent[x];
  }

  auto unite(int x, int y, long long w) -> bool {
    int root_x = find(x);
    int root_y = find(y);
    if (root_x == root_y) {
      return dist[x] - dist[y] - w == 0;
    }

    parent[root_x] = root_y;
    dist[root_x] = dist[y] - dist[x] + w;
    return true;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  std::cin >> t;

  while (t--) {
    int n, m;
    std::cin >> n >> m;
    DisjSet dsu(n + 1);

    bool flag = true;
    while (m--) {
      int a, b, d;
      std::cin >> a >> b >> d;
      if (!dsu.unite(a, b, d)) {
        flag = false;
      }
    }

    std::cout << (flag ? "YES\n" : "NO\n");
  }
}
