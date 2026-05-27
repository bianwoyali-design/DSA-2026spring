#include <iostream>
#include <numeric>
#include <vector>

class DisjSet {
private:
  int n;
  std::vector<int> parent;
  std::vector<int> size;
  std::vector<std::vector<int>> member;

public:
  explicit DisjSet(int n) : n(n), parent(n), size(n, 1), member(n) {
    std::iota(parent.begin(), parent.end(), 0);
    for (int i = 0; i < n; ++i) {
      member[i].emplace_back(i);
    }
  }

  auto find(int x) -> int { return parent[x] == x ? x : find(parent[x]); }

  auto unite(int x, int y, int s) -> int {
    int root_x = find(x);
    int root_y = find(y);

    if (root_x == root_y) {
      return n;
    }

    if (size[root_x] < size[root_y]) {
      std::swap(root_x, root_y);
    }

    size[root_x] += size[root_y];
    for (auto m : member[root_y]) {
      parent[m] = root_x;
      member[root_x].emplace_back(m);
    }
    member[root_y].clear();

    --n;

    if (size[root_x] >= s) {
      n += size[root_x] - 1;
      auto nodes = std::move(member[root_x]);
      for (auto m : nodes) {
        parent[m] = m;
        size[m] = 1;
        member[m].clear();
        member[m].emplace_back(m);
      }
    }

    return n;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, q, s;
  std::cin >> n >> q >> s;
  DisjSet dsu(n);
  while (q--) {
    int a, b;
    std::cin >> a >> b;
    --a;
    --b;
    std::cout << dsu.unite(a, b, s) << '\n';
  }
}
