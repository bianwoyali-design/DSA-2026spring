#include <iostream>
#include <vector>

class SegTree {
  int n = 0;
  std::vector<int> tree{};
  std::vector<int> node{};

public:
  explicit SegTree(const std::vector<int> &data) : n(data.size()) {
    tree.assign(2 * n, 0);
    node.assign(n, 0);
    for (int i = 0; i < n; ++i) {
      tree[i + n] = data[i];
    }
    for (int i = n - 1; i >= 0; --i) {
      tree[i] = std::min(tree[i << 1], tree[i << 1 | 1]);
      node[i] = std::max(tree[i << 1], tree[i << 1 | 1]);
    }
  }

  auto update(int i, const int value) -> void {
    i += n;
    tree[i] = value;

    while (i > 1) {
      tree[i >> 1] = std::min(tree[i], tree[i ^ 1]);
      node[i >> 1] = std::max(tree[i], tree[i ^ 1]);
      i >>= 1;
    }

    node[0] = tree[1];
  }

  auto query() -> std::vector<int> { return node; }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;
  std::vector<int> data(n);
  for (auto &d : data) {
    std::cin >> d;
  }

  SegTree sol(data);
  auto res = sol.query();
  for (const auto &r : res) {
    std::cout << r << ' ';
  }
  std::cout << '\n';

  while (m--) {
    int i, value;
    std::cin >> i >> value;
    sol.update(i, value);
    auto res = sol.query();
    for (const auto &r : res) {
      std::cout << r << ' ';
    }
    std::cout << '\n';
  }
}