#include <iostream>
#include <vector>

class Solution
{
public:
    static bool isTrionic(const std::vector<int> &nums)
    {
        int n = nums.size();
        if (n < 3)
            return false;
        int i = 0;
        while (i + 1 < n && nums[i] < nums[i + 1])
            ++i;
        if (i == 0)
            return false;
        int peak = i;
        while (i + 1 < n && nums[i] > nums[i + 1])
            ++i;
        if (i == peak || i == n - 1)
            return false;
        while (i + 1 < n && nums[i] < nums[i + 1])
            ++i;
        return i == n - 1;
    }
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::vector<int> nums = {3, 7, 1};
    std::cout << Solution::isTrionic(nums) << '\n';
    return 0;
}