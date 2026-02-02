#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

class Solution
{
public:
    long long minimumCost(vector<int> &nums, int k, int dist)
    {
        long long ans = 0, res = 0;
        priority_queue<int, vector<int>> low;
        priority_queue<int, vector<int>, greater<>> up;
        unordered_map<int, int> lmp, ump;
        for (int i = 1; i < k; i++)
        {
            low.push(nums[i]);
            res += nums[i];
        }
        for (int i = k; i < dist + 2; i++)
        {
            if (nums[i] < low.top())
            {
                res -= low.top();
                up.push(low.top());
                low.pop();
                low.push(nums[i]);
                res += nums[i];
            }
            else
                up.push(nums[i]);
        }
        ans = res;
        for (int i = dist + 2; i < nums.size(); i++)
        {
            // 插入
            if (nums[i] <= low.top())
            {
                while (lmp[low.top()])
                {
                    lmp[low.top()]--;
                    low.pop();
                }
                res -= low.top();
                up.push(low.top());
                low.pop();
                low.push(nums[i]);
                res += nums[i];
            }
            else
                up.push(nums[i]);
            // 删除
            if (nums[i - dist - 1] <= low.top())
            {
                lmp[nums[i - dist - 1]]++;
                while (ump[up.top()])
                {
                    ump[up.top()]--;
                    up.pop();
                }
                res -= nums[i - dist - 1];
                res += up.top();
                low.push(up.top());
                up.pop();
            }
            else
                ump[nums[i - dist - 1]]++;
            ans = min(ans, res);
        }
        return ans + nums[0];
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    vector<int> nums = {1, 3, 2, 6, 4, 2};
    int k = 3, dist = 3;
    cout << sol.minimumCost(nums, k, dist) << '\n';
    return 0;
}