#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int minPairSum(vector<int> &nums)
    {
        ranges::sort(nums);

        int l = 0, r = nums.size() - 1;
        int minMaxSum = 0;
        while (l < r)
            minMaxSum = max(minMaxSum, nums[l++] + nums[r--]);

        return minMaxSum;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    vector<int> nums = {3, 5, 4, 2, 4, 6};
    cout << sol.minPairSum(nums) << '\n';
    return 0;
}