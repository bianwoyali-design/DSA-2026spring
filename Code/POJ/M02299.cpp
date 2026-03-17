#include <algorithm>
#include <iostream>
#include <vector>

struct Fenwick {
  int n;
  std::vector<int> tree;
  Fenwick(int n) : n(n), tree(n + 1, 0) {}

  void update(int i) {
    for (; i <= n; i += i & -i)
      ++tree[i];
  }

  auto query(int i) -> int {
    int sum = 0;
    for (; i > 0; i &= i - 1)
      sum += tree[i];
    return sum;
  }
};

void solve() {
  int n;
  while (std::cin >> n && n != 0) {
    std::vector<int> a(n);
    std::vector<int> vals(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> a[i];
      vals[i] = a[i];
    }

    std::sort(vals.begin(), vals.end());
    vals.erase(std::unique(vals.begin(), vals.end()), vals.end());

    Fenwick bit(vals.size());
    long long inversion = 0;

    for (int i = n - 1; i >= 0; --i) {
      int rank = std::lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin() + 1;
      inversion += bit.query(rank - 1);
      bit.update(rank);
    }

    std::cout << inversion << '\n';
  }
}

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  solve();
  return 0;
}