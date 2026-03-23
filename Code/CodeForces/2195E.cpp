#include <iostream>
#include <ranges>
#include <vector>

#define MOD 1000000007

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  std::cin >> t;

  while (t--) {
    int n;
    std::cin >> n;

    std::vector<int> left(n), right(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> left[i] >> right[i];
      --left[i], --right[i];
    }

    std::vector<long long> dp(n);

    auto initialization = [&](this auto &&initialization, int i) -> long long {
      if (left[i] == -1)
        return dp[i] = 1;
      else {
        return dp[i] =
                   (initialization(left[i]) + initialization(right[i]) + 3) %
                   MOD;
      }
    };

    auto compute = [&](this auto &&compute, int i) {
      if (left[i] == -1)
        return;
      else {
        dp[left[i]] = (dp[left[i]] + dp[i]) % MOD;
        dp[right[i]] = (dp[right[i]] + dp[i]) % MOD;
        compute(left[i]);
        compute(right[i]);
      }
    };

    initialization(0);

    compute(0);

    for (auto [i, v] : dp | std::views::enumerate)
      std::cout << v << " \n"[i + 1 == n];
  }
}