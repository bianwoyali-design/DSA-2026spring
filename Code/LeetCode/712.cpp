#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int minimumDeleteSum(string s1, string s2)
    {
        int m = s1.length();
        int n = s2.length();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 1; i <= m; ++i)
            dp[i][0] = dp[i - 1][0] + s1[i - 1];
        for (int j = 1; j <= n; ++j)
            dp[0][j] = dp[0][j - 1] + s2[j - 1];
        
        for (int i = 1; i <= m; ++i)
        {
            int c1 = s1[i - 1];
            for (int j = 1; j <= n; ++j)
            {
                int c2 = s2[j - 1];
                if (c1 == c2)
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = min(dp[i - 1][j] + c1, dp[i][j - 1] + c2);
            }
        }

        return dp[m][n];
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    string s1 = "delete", s2 = "leet";
    Solution sol;
    cout << sol.minimumDeleteSum(s1, s2) << '\n';
    return 0;
}