#include <iostream>
#include <vector>
using namespace std;

class Solution
{
private:
    vector<vector<int>> rowSum;
    vector<vector<int>> colSum;
    bool checkMagicSquare(int i, int j, int edge, vector<vector<int>> &grid)
    {
        int stdSum = rowSum[i][j + edge - 1] - (j ? rowSum[i][j - 1] : 0);
        int d1 = 0, d2 = 0;
        for (int k = 0; k < edge; ++k)
        {
            if (rowSum[i + k][j + edge - 1] - (j ? rowSum[i + k][j - 1] : 0) != stdSum)
                return false;
            if (colSum[i + edge - 1][j + k] - (i ? colSum[i - 1][j + k] : 0) != stdSum)
                return false;
            d1 += grid[i + k][j + k];
            d2 += grid[i + k][j + edge - 1 - k];
        }
        if (d1 != stdSum || d2 != stdSum)
            return false;
        return true;
    }

public:
    int largestMagicSquare(vector<vector<int>> &grid)
    {
        int n = grid.size(), m = grid[0].size();
        rowSum.resize(n, vector<int>(m));
        for (int i = 0; i < n; ++i)
        {
            rowSum[i][0] = grid[i][0];
            for (int j = 1; j < m; ++j)
                rowSum[i][j] = rowSum[i][j - 1] + grid[i][j];
        }

        colSum.resize(n, vector<int>(m));
        for (int i = 0; i < m; ++i)
        {
            colSum[0][i] = grid[0][i];
            for (int j = 1; j < n; ++j)
                colSum[j][i] = colSum[j - 1][i] + grid[j][i];
        }

        for (int edge = min(n, m); edge >= 2; --edge)
            for (int i = 0; i + edge <= n; ++i)
                for (int j = 0; j + edge <= m; ++j)
                    if (checkMagicSquare(i, j, edge, grid))
                        return edge;
        return 1;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    vector<vector<int>> grid = {{7, 1, 4, 5, 6}, {2, 5, 1, 6, 4}, {1, 5, 4, 3, 2}, {1, 2, 7, 3, 4}};
    cout << sol.largestMagicSquare(grid) << '\n';

    return 0;
}