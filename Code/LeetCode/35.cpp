#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  auto searchInsert(vector<int> &nums, int target) -> int {
    int l = 0, r = static_cast<int>(nums.size()) - 1;
    int ans = static_cast<int>(nums.size());
    while (l <= r) {
      int mid = l + ((r - l) >> 1);
      if (nums[mid] >= target) {
        ans = mid;
        r = mid - 1;
      } else
        l = mid + 1;
    }
    return ans;
  }
};

auto main() -> int {
  cin.tie(nullptr)->sync_with_stdio(false);

  vector<int> nums = {1, 3, 5, 6};
  Solution sol;
  cout << sol.searchInsert(nums, 7) << '\n';
  return 0;
}