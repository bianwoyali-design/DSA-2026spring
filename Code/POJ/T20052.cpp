#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

enum class Direction
{
    Left,
    Right,
    Up,
    Down
};

class Solution
{
private:
    int p;
    int maxVal;

    bool process(vector<int> &row)
    {
        int n = row.size();
        vector<int> nextRow(n, 0);
        int writeIdx = 0;
        bool changed = false; // Dirty flag
        for (int i = 0; i < n; ++i)
            if (row[i])
                nextRow[writeIdx++] = row[i];

        for (int i = 0; i < writeIdx - 1; ++i)
        {
            if (nextRow[i] != 0 && nextRow[i] == nextRow[i + 1])
            {
                nextRow[i] *= 2;
                maxVal = max(maxVal, nextRow[i]);

                for (int j = i + 1; j < writeIdx - 1; ++j)
                    nextRow[j] = nextRow[j + 1];
                nextRow[--writeIdx] = 0;
                changed = true;
            }
        }

        if (!changed)
            for (int i = 0; i < n; ++i)
                if (row[i] != nextRow[i])
                {
                    changed = true;
                    break;
                }

        row = move(nextRow);
        return changed;
    }

    bool moveBoard(vector<vector<int>> &grid, Direction dir)
    {
        int m = grid.size(), n = grid[0].size();
        bool gridChanged = false;

        if (dir == Direction::Left || dir == Direction::Right)
            for (auto &g : grid)
            {
                if (dir == Direction::Right)
                    reverse(g.begin(), g.end());
                if (process(g))
                    gridChanged = true;
                if (dir == Direction::Right)
                    reverse(g.begin(), g.end());
            }
        else
            for (int j = 0; j < n; ++j)
            {
                vector<int> v;
                for (auto &g : grid)
                    v.emplace_back(g[j]);
                if (dir == Direction::Down)
                    reverse(v.begin(), v.end());
                if (process(v))
                    gridChanged = true;
                if (dir == Direction::Down)
                    reverse(v.begin(), v.end());
                for (int i = 0; i < m; ++i)
                    grid[i][j] = v[i];
            }

        return gridChanged;
    }

    void dfs(vector<vector<int>> grid, int steps)
    {
        if (steps == p)
            return;

        vector<vector<int>> backup = grid;
        for (auto dir : {Direction::Left, Direction::Right, Direction::Up, Direction::Down})
            // 如果棋盘发生了变化，才继续向下搜索
            if (moveBoard(grid, dir))
            {
                dfs(move(grid), steps + 1);
                grid = backup;
            }
        // move()直接移动，直接把 grid 的所有权移交给下一层递归函数，极大地减少了内存分配和数据复制带来的延迟
    }

public:
    explicit Solution(int p) : p(p), maxVal(0) {}

    int maximumPoint(vector<vector<int>> grid)
    {
        for (const auto &row : grid)
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
