#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    double champagneTower(int poured, int query_row, int query_glass)
    {
        vector<double> dp(query_row + 1, 0);
        dp[0] = poured;

        for (int i = 0; i < query_row; ++i)
            for (int j = i; j >= 0; --j)
            {
                double x = dp[j] - 1;
                if (x > 0)
                {
                    dp[j + 1] += x / 2;
                    dp[j] = x / 2;
                }
                else
                    dp[j] = 0;
            }

        return min(dp[query_glass], 1.0);
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    int poured = 2, query_glass = 1, query_row = 1;
    cout << sol.champagneTower(poured, query_glass, query_row);
    return 0;
}