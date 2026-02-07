#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution
{
public:
    long long maxSum(vector<vector<int>> &grid, vector<int> &limits, int k)
    {
        vector<int> vec;

        for (int i = 0, m = grid.size(); i < m; ++i)
        {
            auto &v = grid[i];
            ranges::nth_element(v, end(v) - limits[i]);
            vec.insert(end(vec), end(v) - limits[i], end(v));
        }

        ranges::nth_element(vec, end(vec) - k);

        return reduce(end(vec) - k, end(vec), 0LL);
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    vector<vector<int>> grid = {{5, 3, 7}, {8, 2, 6}};
    vector<int> limits = {2, 2};
    int k = 3;
    cout << sol.maxSum(grid, limits, k) << '\n';
    return 0;
}