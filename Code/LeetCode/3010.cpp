#include <iostream>
#include <algorithm>
#include <vector>

class Solution
{
public:
    int minimumCost(std::vector<int> &nums)
    {
        int first = nums[0];
        nums.erase(nums.begin());
        std::ranges::sort(nums.begin(), nums.end());
        return nums[0] + nums[1] + first;
    }
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    std::vector<int> nums = {10, 3, 1, 1};
    std::cout << sol.minimumCost(nums) << '\n';
    return 0;
}