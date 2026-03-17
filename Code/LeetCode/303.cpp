#include <iostream>
#include <ranges>
#include <vector>
using namespace std;

class NumArray {
private:
  vector<int> prefixSum;

public:
  NumArray(vector<int> &nums) : prefixSum(nums.size() + 1) {
    for (auto [i, v] : nums | views::enumerate)
      prefixSum[i + 1] = prefixSum[i] + v;
  }

  auto sumRange(int left, int right) -> int {
    return prefixSum[right + 1] - prefixSum[left];
  }
};

auto main() -> int {
  cin.tie(nullptr)->sync_with_stdio(false);

  vector<int> nums = {-2, 0, 3, -5, 2, -1};
  int left = 2, right = 5;
  auto *obj = new NumArray(nums);
  int param_1 = obj->sumRange(left, right);
  cout << param_1 << '\n';
  return 0;
}
