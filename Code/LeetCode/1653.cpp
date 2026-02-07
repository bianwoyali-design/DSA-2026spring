#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int minimumDeletions(string s)
    {
        int dp = 0;
        int cntB = 0;

        for (const auto &c : s)
            if (c == 'a')
                dp = min(dp + 1, cntB);
            else
                ++cntB;

        return dp;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    string s = "bbaaaaabb";
    cout << sol.minimumDeletions(s) << '\n';
    return 0;
}