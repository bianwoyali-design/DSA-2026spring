#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;
  std::vector<int> nums(n);
  int minnum = 1;
  for (int i = 0; i < n; ++i) {
    std::cin >> nums[i];
  }

  std::sort(nums.begin(), nums.end());
  for (int i = 0; i < n; ++i) {
    if (nums[i] == minnum) {
      ++minnum;
    }
  }

  std::cout << minnum << '\n';
}