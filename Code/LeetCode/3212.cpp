#include <print>
#include <vector>

class Solution {
public:
  auto numberOfSubmatrices(std::vector<std::vector<char>> &grid) -> int {
    int n = static_cast<int>(grid[0].size());
    int ans = 0;
    std::vector<std::array<int, 2>> colSum(n);

    for (const auto &row : grid) {
      int s0 = 0, s1 = 0;
      for (int i = 0; i < row.size(); ++i) {
        if (row[i] != '.')
          ++colSum[i][row[i] & 1];
        s0 += colSum[i][0];
        s1 += colSum[i][1];
        if (s0 && s0 == s1)
          ++ans;
      }
    }
    return ans;
  }
};

auto main() -> int {
  auto sol = new Solution;
  std::vector<std::vector<char>> grid = {{'.', '.', '.'}, {'.', '.', '.'}};
  std::println("{}", sol->numberOfSubmatrices(grid));
}