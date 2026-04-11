#include <algorithm>
#include <climits>
#include <cstddef>
#include <iostream>
#include <vector>

class Solution {
  constexpr static int MOD = 1000000007;

public:
  auto maxProductPath(std::vector<std::vector<int>> &grid) -> int {
    size_t m = grid.size();
    size_t n = grid[0].size();

    std::vector<long long> dp_max(n), dp_min(n);

    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j) {
        long long x = grid[i][j];
        if (i == 0 && j == 0) {
          dp_max[0] = x, dp_min[0] = x;
          continue;
        }

        long long res_max = LLONG_MIN;
        long long res_min = LLONG_MAX;
        if (i > 0) {
          long long mx = dp_max[j], mn = dp_min[j];
          res_max = std::max(mx * x, mn * x);
          res_min = std::min(mx * x, mn * x);
        }
        if (j > 0) {
          long long mx = dp_max[j - 1], mn = dp_min[j - 1];
          res_max = std::max({res_max, mx * x, mn * x});
          res_min = std::min({res_min, mx * x, mn * x});
        }

        dp_max[j] = res_max;
        dp_min[j] = res_min;
      }

    long long ans = dp_max[n - 1];
    return ans < 0 ? -1 : static_cast<int>(ans % MOD);
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::vector grid(3, std::vector<int>(3));
  grid = {{1, -2, 1}, {1, -2, 1}, {3, -4, 1}};
  Solution sol;
  std::cout << sol.maxProductPath(grid) << '\n';
}