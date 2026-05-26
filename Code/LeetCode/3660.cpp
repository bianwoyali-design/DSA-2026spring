#include <iostream>
#include <limits>
#include <ranges>
#include <vector>

class Solution {
public:
  auto maxValue(std::vector<int> &nums) -> std::vector<int> {
    int n = nums.size();

    std::vector<int> preMax(n, 0);
    preMax[0] = nums[0];
    for (int i = 1; i < n; ++i) {
      preMax[i] = std::max(preMax[i - 1], nums[i]);
    }

    int sufMin = std::numeric_limits<int>::max();
    std::vector<int> dp(n, 0);
    for (int i = n - 1; i >= 0; --i) {
      dp[i] = preMax[i] <= sufMin ? preMax[i] : dp[i + 1];
      sufMin = std::min(sufMin, nums[i]);
    }

    return dp;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::vector<int> nums = {2, 1, 3};
  Solution sol;
  auto ans = sol.maxValue(nums);
  for (auto [i, v] : std::ranges::views::zip(std::views::iota(0), ans)) {
    std::cout << v << " \n"[i + 1 == nums.size()];
  }
}