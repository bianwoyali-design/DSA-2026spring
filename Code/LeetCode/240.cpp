#include <iostream>
#include <vector>

class Solution {
public:
  auto searchMatrix(std::vector<std::vector<int>> &matrix, int target) -> bool {
    int i = static_cast<int>(matrix.size() - 1), j = 0;
    while (i >= 0 && j < matrix[0].size()) {
      if (matrix[i][j] < target)
        ++j;
      else if (matrix[i][j] > target)
        --i;
      else
        return true;
    }
    return false;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::vector matrix(5, std::vector<int>(5));
  matrix = {{1, 4, 7, 11, 15},
            {2, 5, 8, 12, 19},
            {3, 6, 9, 16, 22},
            {10, 13, 14, 17, 24},
            {18, 21, 23, 26, 30}};
  int target = 5;
  Solution sol;
  std::cout << sol.searchMatrix(matrix, target) << '\n';
}