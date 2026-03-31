#include <array>
#include <deque>
#include <print>
#include <vector>

class Solution {
  const std::array<std::array<int, 2>, 4> DIR{
      {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}};

public:
  auto orangesRotting(std::vector<std::vector<int>> &grid) -> int {
    int m = static_cast<int>(grid.size()), n = static_cast<int>(grid[0].size());
    int fresh = 0;
    std::deque<std::pair<int, int>> q;
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 1)
          ++fresh;
        if (grid[i][j] == 2)
          q.emplace_back(i, j);
      }

    int ans = 0;
    while (fresh && !q.empty()) {
      ++ans;
      int sz = static_cast<int>(q.size());
      while (sz--) {
        auto [currx, curry] = q.front();
        q.pop_front();
        for (const auto [x, y] : DIR) {
          int newx = currx + x, newy = curry + y;
          if (newx >= 0 && newx < m && newy >= 0 && newy < n &&
              grid[newx][newy] == 1) {
            q.emplace_back(newx, newy);
            --fresh;
            grid[newx][newy] = 2;
          }
        }
      }
    }

    return fresh ? -1 : ans;
  }
};

auto main() -> int {
  auto sol = new Solution;
  std::vector<std::vector<int>> grid = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
  std::println("{}", sol->orangesRotting(grid));
}