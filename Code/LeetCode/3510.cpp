#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using LL = long long;

struct cmp
{
    bool operator()(pair<LL, int> &a, pair<LL, int> &b)
    {
        return a.first != b.first ? a.first > b.first : a.second > b.second;
    }
};

class Solution
{
public:
    int minimumPairRemoval(vector<int> &nums)
    {
        int n = nums.size(), ans = 0, i, desc = 0;
        priority_queue<pair<LL, int>, vector<pair<LL, int>>, cmp> pq;

        for (i = n - 2; i > -1; --i)
        {
            if (nums[i] > nums[i + 1])
                ++desc;
            pq.emplace(nums[i] + nums[i + 1], i);
        }

        vector<int> l(n + 1), r(n);
        for (i = 0; i <= n; ++i)
            l[i] = i - 1;
        for (i = 0; i < n; ++i)
            r[i] = i + 1;

        vector<LL> x(nums.begin(), nums.end());
        while (desc)
        {
            ++ans;

            while (r[pq.top().second] == n || pq.top().first != x[pq.top().second] + x[r[pq.top().second]])
                pq.pop();

            auto [s, j] = pq.top();
            pq.pop();

            int nxt = r[j];
            if (x[j] > x[nxt])
                --desc;
            if (l[j] != -1)
            {
                if (x[l[j]] > x[j])
                    --desc;
                if (x[l[j]] > s)
                    ++desc;
                pq.emplace(x[l[j]] + s, l[j]);
            }

            int nxt2 = r[nxt];
            if (nxt2 < n)
            {
                if (x[nxt] > x[nxt2])
                    --desc;
                if (s > x[nxt2])
                    ++desc;
                pq.emplace(s + x[nxt2], j);
            }

            x[j] = s;
            r[nxt] = n;
            r[j] = nxt2;
            l[nxt2] = j;
        }
        return ans;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    vector<int> nums = {5, 2, 3, 1};
    cout << sol.minimumPairRemoval(nums) << '\n';
    return 0;
}