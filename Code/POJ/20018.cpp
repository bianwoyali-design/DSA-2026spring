#include <algorithm>
#include <iostream>
#include <vector>

class Fenwick {
private:
  int n;
  std::vector<int> tree;
public:
  explicit Fenwick(int n) : n(n), tree(n + 1, 0) {}
  auto update(int i) -> void {
    while (i <= n) {
      tree[i] += 1;
      i += (i & -i);
    }
  }
  auto query(int i) -> long long {
    long long sum = 0;
    while (i > 0) {
      sum += tree[i];
      i &= i - 1;
    }
    return sum;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;

  std::vector<int> vals(n), rank(n);
  for (auto &&v : vals) {
    std::cin >> v;
  }
  rank = vals;

  std::sort(rank.begin(), rank.end());
  rank.erase(std::unique(rank.begin(), rank.end()), rank.end());

  Fenwick bit(n);

  long long ans = 0;
  for (auto v : vals) {
    int idx = std::upper_bound(rank.begin(), rank.end(), v) - rank.begin() + 1;
    ans += bit.query(idx - 1);
    bit.update(idx);
  }

  std::cout << ans << '\n';
}