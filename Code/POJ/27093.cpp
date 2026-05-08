#include <algorithm>
#include <iostream>
#include <vector>

class SegTree {
  int n = 0;
  std::vector<int> tree{};

public:
  explicit SegTree(int size) {
    int base = 1;
    while (base < size) {
      base <<= 1;
    }
    n = base;
    tree.assign(base << 1, 0);
  }

  auto update(int i, int value) -> void {
    i += n;
    tree[i] = value;

    while (i > 1) {
      tree[i >> 1] = std::max(tree[i], tree[i ^ 1]);
      i >>= 1;
    }
  }

  auto query(int l, int r) -> int {
    l += n;
    r += n;
    int res = 0;

    while (l < r) {
      if (l & 1) {
        res = std::max(res, tree[l++]);
      }
      if (r & 1) {
        res = std::max(res, tree[--r]);
      }
      l >>= 1;
      r >>= 1;
    }
    return res;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int N, D;
  std::cin >> N >> D;

  std::vector<int> data(N, 0);
  for (auto &d : data) {
    std::cin >> d;
  }

  auto index = data;
  std::sort(index.begin(), index.end());
  index.erase(std::unique(index.begin(), index.end()), index.end());

  SegTree seg(index.size());

  std::vector<std::vector<int>> res(N + 1);
  for (int d : data) {
    int idx = std::lower_bound(index.begin(), index.end(), d) - index.begin();
    int left =
        std::lower_bound(index.begin(), index.end(), d - D) - index.begin();
    int right =
        std::upper_bound(index.begin(), index.end(), d + D) - index.begin();

    int layer =
        std::max(seg.query(0, left), seg.query(right, index.size())) + 1;

    res[layer].emplace_back(d);
    seg.update(idx, layer);
  }

  for (auto r : res) {
    if (r.empty()) {
      continue;
    }
    std::sort(r.begin(), r.end());
    for (int a : r) {
      std::cout << a << ' ';
    }
  }
  std::cout << '\n';
}
