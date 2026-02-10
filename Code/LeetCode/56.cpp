#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        if (intervals.size() == 0)
            return {};

        ranges::sort(intervals);
        vector<vector<int>> ret;
        ret.push_back(intervals.front());
        for (auto [i, interval] : intervals | views::enumerate)
        {
            if (ret.back().back() >= interval.front() && ret.back().back() < interval.back())
                ret.back()[1] = interval.back();
            else if (ret.back().back() < interval.front())
                ret.push_back(interval);
        }

        return ret;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    for (const auto &m : sol.merge(intervals))
        cout << m.front() << "," << m.back() << ' ';
    return 0;
}