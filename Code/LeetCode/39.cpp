#include <iostream>
#include <vector>

class Solution {
public:
  auto combinationSum(std::vector<int> &candidates, int target)
      -> std::vector<std::vector<int>> {
    int n = static_cast<int>(candidates.size());
    
    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(target + 1));
    dp[0][0] = true;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j <= target; ++j)
        dp[i + 1][j] =
            dp[i][j] || (candidates[i] <= j && dp[i + 1][j - candidates[i]]);

    std::vector<std::vector<int>> res;
    std::vector<int> comb;
    auto dfs = [&](this auto &&dfs, int i, int left) -> void {
      if (left == 0) {
        res.push_back(comb);
        return;
      }

      if (left < 0 || !dp[i + 1][left])
        return;

      dfs(i - 1, left);

      comb.push_back(candidates[i]);
      dfs(i, left - candidates[i]);
      comb.pop_back();
    };

    dfs(n - 1, target);
    return res;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  auto *sol = new Solution;
  std::vector<int> candidates = {2, 3, 5};
  int target = 8;
  for (const auto &array : sol->combinationSum(candidates, target)) {
    for (const int a : array)
      std::cout << a << ' ';
    std::cout << '\n';
  }
}