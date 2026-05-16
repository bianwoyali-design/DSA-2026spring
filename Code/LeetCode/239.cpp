#include <cstddef>
#include <deque>
#include <ranges>
#include <iostream>
#include <vector>

class Solution {
public:
  auto maxSlidingWindow(const std::vector<int> &nums, int k) -> std::vector<int> {
    size_t n = nums.size();
    std::deque<int> q;
    std::vector<int> ans(n - k + 1);

    for (int i = 0; i < n; ++i) {
      while (!q.empty() && nums[q.back()] < nums[i]) {
        q.pop_back();
      }
      q.push_back(i);

      int left = i - k + 1;
      if (q.front() < left) {
        q.pop_front();
      }

      if (left >= 0) {
        ans[left] = nums[q.front()];
      }
    }

    return ans;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  Solution sol;
  int k = 3;
  std::vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
  auto res = sol.maxSlidingWindow(nums, k);
  for (auto [i, v] : std::ranges::views::zip(std::views::iota(0), res)) {
    std::cout << v << " \n"[i == nums.size() - k];
  }
}