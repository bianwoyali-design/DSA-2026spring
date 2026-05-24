#include <iostream>
#include <numeric>
#include <vector>

class DisjSet {
  std::vector<int> parent;
  std::vector<int> dist;
  std::vector<int> length;

public:
  explicit DisjSet(int n) : parent(n), dist(n, 0), length(n, 1) {
    std::ranges::iota(parent, 0);
  }

  auto find(int x) -> int {
    if (parent[x] == x) {
      return x;
    }
    int old_parent = parent[x];
    parent[x] = find(parent[x]);
    dist[x] += dist[old_parent];
    return parent[x];
  }

  auto unite(int x, int y) -> bool {
    int root_x = find(x);
    int root_y = find(y);
    if (root_x == root_y) {
      return false;
    }
    parent[root_x] = root_y;
    dist[root_x] += length[root_y];
    length[root_y] += length[root_x];
    return true;
  }

  auto check(int x, int y) -> int {
    int root_x = find(x);
    int root_y = find(y);
    if (root_x == root_y) {
      return std::abs(dist[x] - dist[y]) - 1;
    }
    return -1;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  DisjSet dsu(30000);
  int n{};
  std::cin >> n;
  while (n--) {
    char operation;
    int i, j;
    std::cin >> operation >> i >> j;
    if (operation == 'M') {
      dsu.unite(i - 1, j - 1);
    } else {
      std::cout << dsu.check(i - 1, j - 1) << '\n';
    }
  }
}