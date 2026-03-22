#include <iostream>
#include <vector>

#define MOD 998244353

class Fenwick {
private:
  int n;
  std::vector<int> tree;

public:
  explicit Fenwick(int n) : n(n), tree(n + 1, 0) {}

  void update(int i);

  auto query(int i) -> int;
};

void Fenwick::update(int i) {
  while (i <= n) {
    ++tree[i];
    i += (i & -i);
  }
}

auto Fenwick::query(int i) -> int {
  int sum = 0;
  while (i > 0) {
    sum += tree[i];
    i &= i - 1;
  }
  return sum;
}

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;

  std::vector<int> permutaion(n);
  for (int &v : permutaion) {
    std::cin >> v;
  }

  std::vector<int> fact(n);
  fact[0] = 1;
  for (int i = 1; i < n; ++i)
    fact[i] = (int)(1LL * fact[i - 1] * i) % MOD;

  Fenwick BIT(n);

  long long ans = 1;
  for (int i = n - 1; i >= 0; --i) {
    ans = (ans + 1LL * BIT.query(permutaion[i] - 1) * fact[n - 1 - i]) % MOD;
    BIT.update(permutaion[i]);
  }

  std::cout << ans << '\n';
}