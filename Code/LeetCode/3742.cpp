#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

class Solution {
public:
  auto maxPathScore(std::vector<std::vector<int>> &grid, int k) -> int {
    int m = grid.size(), n = grid[0].size();
    std::vector dp(
        m + 1, std::vector(n + 1, std::vector<int>(
                                      k + 2, std::numeric_limits<int>::min())));
    std::fill(dp[0][1].begin() + 1, dp[0][1].end(), 0);

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        int x = grid[i][j];
        for (int cost = 0; cost <= k; ++cost) {
          int prev_k = cost - (x > 0);
          dp[i + 1][j + 1][cost + 1] =
              x + std::max(dp[i][j + 1][prev_k + 1], dp[i + 1][j][prev_k + 1]);
        }
      }
    }
    return dp[m][n][k + 1] < 0 ? -1 : dp[m][n][k + 1];
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::vector<std::vector<int>> grid = {{0, 1}, {1, 2}};
  int k = 1;
  Solution sol;
  std::cout << sol.maxPathScore(grid, k) << '\n';
}