#include <iostream>
#include <ranges>
#include <vector>
using namespace std;

class Solution
{
public:
    int longestBalanced(string s)
    {
        int res = 0, n = s.size();

        for (int i = 0; i < n; ++i)
        {
            if (n - i <= res)
                break;

            vector<int> cnt(26, 0);
            int maxn = 0, v = 0;
            for (int j = i; j < n; ++j)
            {
                int it = s[j] - 'a';
                if (++cnt[it] == 1)
                    ++v;
                maxn = max(maxn, cnt[it]);
                if (maxn * v == j - i + 1)
                    res = max(res, j - i + 1);
            }
        }

        return res;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    string s = "zzabccy";
    cout << sol.longestBalanced(s) << '\n';
    return 0;
}