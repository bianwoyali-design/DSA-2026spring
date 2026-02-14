#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution
{
    int f(string &s, char x, char y)
    {
        int n = s.length();
        int res = 0;
        unordered_map<int, int> h;
        for (int i = 0; i < n; ++i)
        {
            if (s[i] != x && s[i] != y)
                continue;

            h.clear();
            h[0] = i - 1;
            int diff = 0;
            while (i < n && (s[i] == x || s[i] == y))
            {
                diff += s[i] == x ? 1 : -1;
                if (h.contains(diff))
                    res = max(res, i - h[diff]);
                else
                    h[diff] = i;
                ++i;
            }
        }

        return res;
    }

public:
    int longestBalanced(string s)
    {
        int n = s.length();
        int res = 0;

        // 1种字符
        int last = 0;
        for (int i = 0; i < n; ++i)
        {
            if (i > 0 && s[i] == s[i - 1])
                ++last;
            else
                last = 1;
            res = max(res, last);
        }

        // 2种字符
        res = max(res, f(s, 'a', 'b'));
        res = max(res, f(s, 'b', 'c'));
        res = max(res, f(s, 'a', 'c'));

        // 3种字符
        auto getId = [&](int x, int y) -> long long
        {
            return 1ll * (x + n) << 32 | (y + n);
        };

        unordered_map<long long, int> h = {{getId(0, 0), -1}};
        int pre[3] = {0, 0, 0};
        for (int i = 0; i < n; ++i)
        {
            ++pre[s[i] - 'a'];
            long long id = getId(pre[0] - pre[1], pre[1] - pre[2]);
            if (h.contains(id))
                res = max(res, i - h[id]);
            else
                h[id] = i;
        }
        return res;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    string s = "a";
    cout << sol.longestBalanced(s) << '\n';
    return 0;
}