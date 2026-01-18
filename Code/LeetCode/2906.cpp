#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>> &grid)
    {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> p(n, vector<int>(m));

        int prefixSum = 1;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
            {
                p[i][j] = prefixSum;
                prefixSum = (size_t)prefixSum * grid[i][j] % 12345;
            }

        int suffixSum = 1;
        for (int i = n - 1; i >= 0; --i)
            for (int j = m - 1; j >= 0; --j)
            {
                p[i][j] = (size_t)p[i][j] * suffixSum % 12345;
                suffixSum = (size_t)suffixSum * grid[i][j] % 12345;
            }

        return p;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    vector<vector<int>> grid = {{12345}, {2}, {1}};

    for (const auto &p : sol.constructProductMatrix(grid))
        for (const auto &a : p)
            cout << a << ' ';
    return 0;
}