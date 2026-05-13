#include <iostream>
#include <vector>

class DSU {
  std::vector<int> parent;
  std::vector<int> rank;

public:
  explicit DSU(int n) : parent(n), rank(n, 0) {
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }

  auto find(int x) -> int {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }

  auto unite(int a, int b) -> void {
    int root_a = find(a);
    int root_b = find(b);
    if (root_a == root_b) {
      return;
    }

    if (rank[root_a] < rank[root_b]) {
      parent[root_a] = root_b;
    } else if (rank[root_a] > rank[root_b]) {
      parent[root_b] = root_a;
    } else {
      parent[root_b] = root_a;
      ++rank[a];
    }
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t{};
  std::cin >> t;
  for (int i = 1; i <= t; ++i) {
    int n{}, m{};
    std::cin >> n >> m;

    bool flag = false;
    DSU dsu(2 * n + 1);
    while (m--) {
      int a, b;
      std::cin >> a >> b;

      if (dsu.find(a) == dsu.find(b)) {
        flag = true;
      }

      dsu.unite(a, b + n);
      dsu.unite(b, a + n);
    }

    std::cout << "Scenario #" << i << ":\n";
    std::cout << (flag ? "Suspicious bugs found!" : "No suspicious bugs found!") << "\n\n";
  }
}