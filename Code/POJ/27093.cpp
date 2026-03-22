#include <algorithm>
#include <iostream>
#include <vector>

template <typename Tp> class Fenwick {
private:
  int n;
  std::vector<Tp> tree;

public:
  explicit Fenwick(int n) : n(n), tree(n + 1, -1) {}

  auto update(int i, Tp layer) -> void;

  [[nodiscard]] auto getMax(int i) const -> Tp;
};

template <typename Tp> auto Fenwick<Tp>::update(int i, Tp layer) -> void {
  while (i <= n) {
    tree[i] = std::max(tree[i], layer);
    i += (i & -i);
  }
}

template <typename Tp>
[[nodiscard]] auto Fenwick<Tp>::getMax(int i) const -> Tp {
  Tp res = -1;
  while (i > 0) {
    res = std::max(res, tree[i]);
    i &= i - 1;
  }
  return res;
}

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int N, D;
  std::cin >> N >> D;

  std::vector<int> v(N), val(N);
  for (int i = 0; i < N; ++i) {
    std::cin >> v[i];
    val[i] = v[i];
  }

  std::ranges::sort(v);
  auto [first, last] = std::ranges::unique(v);
  v.erase(first, last);
  int l = (int)v.size();

  std::vector<std::vector<int>> res(N + 1);

  Fenwick<int> bit_l(l), bit_r(l);

  for (const int x : val) {
    int index = std::ranges::lower_bound(v, x) - v.begin() + 1;
    int left = std::ranges::upper_bound(v, x - D - 1) - v.begin();
    int right = l - (std::ranges::lower_bound(v, x + D + 1) - v.begin());

    int layer = 1 + std::max(bit_l.getMax(left), bit_r.getMax(right));

    bit_l.update(index, layer);
    bit_r.update(l + 1 - index, layer);

    res[layer].push_back(x);
  }

  for (auto &r : res) {
    if (r.empty())
      continue;
    std::ranges::sort(r);
    for (const int x : r)
      std::cout << x << ' ';
  }
}