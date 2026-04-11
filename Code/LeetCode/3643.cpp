#include <iostream>
#include <utility>
#include <vector>

class Solution {
public:
  auto reverseSubmatrix(std::vector<std::vector<int>> &grid, int x, int y,
                        int k) -> std::vector<std::vector<int>> {
    for (int i = 0; i < k / 2; ++i)
      for (int j = 0; j < k; ++j)
        std::swap(grid[x + i][y + j], grid[x + k - 1 - i][y + j]);
    return std::move(grid);
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::vector grid(4, std::vector<int>(4));
  grid = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
  Solution sol;
  auto res = sol.reverseSubmatrix(grid, 1, 0, 3);
  for (const auto &row : res) {
    for (const auto v : row)
      std::cout << v << ' ';
    std::cout << '\n';
  }
}