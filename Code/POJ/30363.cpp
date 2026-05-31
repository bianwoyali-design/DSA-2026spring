#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

class DisjSet {
  int n;
  long long comb = 0;
  std::vector<int> parent;
  std::vector<long long> size;

public:
  explicit DisjSet(int n) : n(n), parent(n), size(n, 1) {
    std::iota(parent.begin(), parent.end(), 0);
  }

  auto find(int x) -> int { return parent[x] == x ? x : find(parent[x]); }

  auto unite(int x, int y) -> long long {
    int root_x = find(x);
    int root_y = find(y);

    if (root_x == root_y) {
      return comb;
    }

    if (size[root_x] < size[root_y]) {
      std::swap(root_x, root_y);
    }
    long long cx = size[root_x] * (size[root_x] - 1) / 2;
    long long cy = size[root_y] * (size[root_y] - 1) / 2;
    parent[root_y] = root_x;
    size[root_x] += size[root_y];
    comb += (size[root_x] * (size[root_x] - 1) / 2) - cx - cy;
    return comb;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;
  DisjSet dsu(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    std::cout << dsu.unite(--u, --v) << '\n';
  }
}