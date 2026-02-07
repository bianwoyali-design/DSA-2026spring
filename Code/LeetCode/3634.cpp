#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int minRemoval(std::vector<int> &nums, int k)
    {
        int n = nums.size();
        std::ranges::sort(nums);

        int r = 0, ans = n;
        for (int l = 0; l < n; ++l)
        {
            while (r < n && nums[r] <= (long long)nums[l] * k)
                ++r;
            ans = std::min(ans, n - (r - l));
        }

        return ans;
    }
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    std::vector<int> nums = {1, 34, 23};
    int k = 2;
    std::cout << sol.minRemoval(nums, k) << '\n';
    return 0;
}