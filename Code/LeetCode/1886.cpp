#include <iostream>
#include <vector>

class Solution {
public:
  auto findRotation(std::vector<std::vector<int>> &mat,
                    std::vector<std::vector<int>> &target) -> bool {
    size_t n = mat.size();
    int status = 0xF;

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j) {
        int x = target[i][j];
        if (x != mat[i][j])
          status &= ~(1 << 0);
        if (x != mat[j][n - i - 1])
          status &= ~(1 << 1);
        if (x != mat[n - i - 1][n - j - 1])
          status &= ~(1 << 2);
        if (x != mat[n - j - 1][i])
          status &= ~(1 << 3);
        if (status == 0)
          return false;
      }
    return true;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  std::vector<std::vector<int>> mat, target;
  mat = {{0, 0, 0}, {0, 1, 0}, {1, 1, 1}};
  target = {{1, 1, 1}, {0, 1, 0}, {0, 0, 0}};
  Solution sol;
  std::cout << sol.findRotation(mat, target) << '\n';
}