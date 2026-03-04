#include <iostream>
#include <ranges>
#include <vector>
using namespace std;

class Solution
{
private:
    int collect(vector<int> row)
    {
        int i = row.size() - 1;
        while (i >= 0 && row[i] == 0)
            --i;
        return row.size() - i - 1;
    }

public:
    int minSwaps(vector<vector<int>> &grid)
    {
        int n = grid.size();
        vector<int> counter(n);
        for (auto [i, v] : grid | views::enumerate)
            counter[i] = collect(v);

        int steps = 0;
        for (int i = 0; i < n; ++i)
        {
            if (counter[i] < n - i - 1)
            {
                for (int j = i + 1; j < n; ++j)
                {
                    swap(counter[i], counter[j]);
                    ++steps;
                    if (counter[i] >= n - i - 1)
                        break;
                }
                if (counter[i] < n - i - 1)
                    return -1;
            }
        }

        return steps;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    vector<vector<int>> grid = {{0, 0, 1}, {1, 1, 0}, {1, 0, 0}};
    cout << sol.minSwaps(grid) << '\n';
    return 0;
}