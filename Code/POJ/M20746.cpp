#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string line;
  std::getline(std::cin, line);

  std::vector<int> nums;
  std::stringstream ss(line);
  std::string part;

  while (std::getline(ss, part, ',')) {
    nums.emplace_back(std::stoi(part));
  }

  int t;
  std::cin >> t;

  auto can_finish = [&](int k) -> bool {
    int total = 0;
    for (auto work : nums) {
      total += (work + k - 1) / k;
      if (total > t) {
        return false;
      }
    }
    return true;
  };

  int left = 1;
  int right = *std::max_element(nums.begin(), nums.end());
  while (left < right) {
    int mid = left + (right - left) / 2;
    if (can_finish(mid)) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }

  std::cout << left << '\n';
}
