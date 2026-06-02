#include <algorithm>
#include <cmath>
#include <iomanip>
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
    std::ranges::iota(parent, 0);
  }

  auto find(int x) -> int { return parent[x] == x ? x : find(parent[x]); }

  auto unite(int x, int y) -> bool {
    int root_x = find(x);
    int root_y = find(y);

    if (root_x == root_y) {
      return false;
    }

    if (rank[root_y] < rank[root_x]) {
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

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int s, p;
  std::cin >> s >> p;
  std::vector<std::pair<int, int>> point(p);
  std::vector<std::tuple<double, int, int>> edges;
  for (auto &&[x, y] : point) {
    std::cin >> x >> y;
  }

  for (int i = 0; i < p; ++i) {
    for (int j = i + 1; j < p; ++j) {
      int xi = point[i].first, xj = point[j].first;
      int yi = point[i].second, yj = point[j].second;
      double dist = std::sqrt((xi - xj) * (xi - xj) + (yi - yj) * (yi - yj));
      edges.emplace_back(dist, i, j);
    }
  }

  DisjSet dsu(p);
  std::ranges::sort(edges);

  int count = 0;
  for (auto [w, u, v] : edges) {
    if (dsu.unite(u, v)) {
      ++count;
      if (count == p - s) {
        std::cout << std::fixed << std::setprecision(2) << w << '\n';
      }
    }
  }
}