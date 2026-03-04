#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Solution
{
private:
    int p;
    int maxVal;

    bool process(vector<int> &row)
    {
        bool changed = false; // Dirty flag
        int n = row.size();

        int writeIdx = 0;
        for (int i = 0; i < n; ++i)
        {
            if (row[i] != 0)
            {
                if (writeIdx != i)
                    changed = true;
                row[writeIdx++] = row[i];
            }
        }
        for (int i = writeIdx; i < n; ++i)
        {
            if (row[i] != 0)
                changed = true;
            row[i] = 0;
        }

        for (int i = 0; i + 1 < n && row[i] != 0; ++i)
        {
            if (row[i] == row[i + 1])
            {
                row[i] *= 2;
                maxVal = max(maxVal, row[i]);
                changed = true;

                for (int j = i + 1; j + 1 < n; ++j)
                    row[j] = row[j + 1];
                row[n - 1] = 0;
            }
        }
        return changed;
    }

    bool moveBoard(vector<vector<int>> &grid, int dict)
    {
        int m = grid.size(), n = grid[0].size();
        bool gridChanged = false;

        switch (dict)
        {
        case 0: // Left
            for (auto &g : grid)
                if (process(g))
                    gridChanged = true;
            break;

        case 1: // Right
            for (auto &g : grid)
            {
                reverse(g.begin(), g.end());
                if (process(g))
                    gridChanged = true;
                reverse(g.begin(), g.end());
            }
            break;

        case 2: // Up
            for (int j = 0; j < n; ++j)
            {
                vector<int> v;
                for (auto &g : grid)
                    v.emplace_back(g[j]);
                if (process(v))
                    gridChanged = true;
                for (int i = 0; i < m; ++i)
                    grid[i][j] = v[i];
            }
            break;

        case 3: // Down
            for (int j = 0; j < n; ++j)
            {
                vector<int> v;
                for (auto &g : grid)
                    v.emplace_back(g[j]);
                reverse(v.begin(), v.end());
                if (process(v))
                    gridChanged = true;
                reverse(v.begin(), v.end());
                for (int i = 0; i < m; ++i)
                    grid[i][j] = v[i];
            }
            break;
        }

        return gridChanged;
    }

    void dfs(vector<vector<int>> grid, int steps)
    {
        if (steps == p)
            return;

        for (int i = 0; i < 4; ++i)
        {
            vector<vector<int>> nextGrid = grid;
            // 如果棋盘发生了变化，才继续向下搜索
            if (moveBoard(nextGrid, i))
                dfs(move(nextGrid), steps + 1);
            // move()直接移动，直接把 nextGrid 的所有权移交给下一层递归函数，极大地减少了内存分配和数据复制带来的延迟
        }
    }

public:
    Solution(int p) : p(p), maxVal(0) {}

    int maximumPoint(vector<vector<int>> grid)
    {
        for (auto &row : grid)
            for (int val : row)
                maxVal = max(maxVal, val);
        dfs(grid, 0);
        return maxVal;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int m, n, p;
    cin >> m >> n >> p;
    vector<vector<int>> grid(m, vector<int>(n));

    for (auto &g : grid)
        for (auto &v : g)
            cin >> v;

    Solution sol(p);
    cout << sol.maximumPoint(grid) << '\n';
    return 0;
}