#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>

class DisjSet {
private:
  std::vector<int> parent;
  std::vector<int> rank;

public:
  explicit DisjSet(int n) : parent(n), rank(n, 0) {
    std::iota(parent.begin(), parent.end(), 0);
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

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;
  std::vector grid(n, std::vector<int>(m));
  for (auto &row : grid) {
    for (int &x : row) {
      std::cin >> x;
    }
  }

  std::vector<std::tuple<int, int, int>> edges;
  constexpr static std::array<std::array<int, 2>, 2> dir = {{{0, 1}, {1, 0}}};
  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < m; ++y) {
      int u = x * m + y;
      for (const auto &[dx, dy] : dir) {
        int nx = x + dx;
        int ny = y + dy;
        if (nx >= n || ny >= m) {
          continue;
        }
        int v = nx * m + ny;
        int w = std::abs(grid[nx][ny] - grid[x][y]);
        edges.emplace_back(w, u, v);
      }
    }
  }

  if (n == 1 && m == 1) {
    std::cout << 0 << '\n';
    return 0;
  }

  std::sort(edges.begin(), edges.end());
  DisjSet dsu(n * m);
  for (auto [w, u, v] : edges) {
    if (dsu.unite(u, v)) {
      if (dsu.find(0) == dsu.find(n * m - 1)) {
        std::cout << w << '\n';
        return 0;
      }
    }
  }
}
