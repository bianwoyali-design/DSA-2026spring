#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

class Solution {
  auto rotate(std::vector<std::vector<int>> grid)
      -> std::vector<std::vector<int>> {
    int m = grid.size(), n = grid[0].size();
    std::vector rotated_grid(n, std::vector<int>(m));

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        rotated_grid[j][m - 1 - i] = grid[i][j];
      }
    }

    return rotated_grid;
  }

public:
  auto canPartitionGrid(std::vector<std::vector<int>> &grid) -> bool {
    long long total = 0;
    for (auto &&g : grid) {
      for (auto v : g) {
        total += v;
      }
    }

    auto check = [&](std::vector<std::vector<int>> g) -> bool {
      int m = g.size(), n = g[0].size();

      auto f = [&]() -> bool {
        std::unordered_set<long long> set = {0};
        long long s = 0;
        for (int i = 0; i < m - 1; ++i) {
          auto &row = g[i];
          for (int j = 0; j < n; ++j) {
            int v = row[j];
            s += v;
            if (i > 0 || j == 0 || j == n - 1) {
              set.insert(v);
            }
          }

          if (n == 1) {
            if (s * 2 == total || s * 2 - total == g[0][0] ||
                s * 2 - total == row[0]) {
              return true;
            }
            continue;
          }

          if (set.contains(2 * s - total)) {
            return true;
          }

          if (i == 0) {
            for (auto v : row) {
              set.insert(v);
            }
          }
        }

        return false;
      };

      if (f()) {
        return true;
      }
      std::ranges::reverse(g);
      return f();
    };

    return check(grid) || check(rotate(grid));
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::vector<std::vector<int>> grid = {{1, 2}, {3, 4}};
  Solution sol;
  std::cout << sol.canPartitionGrid(grid) << '\n';
}