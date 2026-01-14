#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    string longestPalindrome(string s)
    {
        if (s.empty())
            return "";
        string t = "$#";
        for (const auto &c : s)
            t += c, t += '#';
        t += '$';
        int r = 0, c = 0;
        vector<int> p(t.size());
        int maxLen = 0, center = 0;
        for (int i = 1; i < (int)t.size() - 1; ++i)
        {
            if (i < r)
                p[i] = min(p[(c << 1) - i], r - i);
            else
                p[i] = 1;
            while (i - p[i] >= 0 && i + p[i] < (int)t.size() && t[i - p[i]] == t[i + p[i]])
                ++p[i];
            if (i + p[i] > r)
            {
                r = i + p[i];
                c = i;
            }
        }
        for (int i = 1; i < (int)t.size() - 1; ++i)
            if (p[i] - 1 > maxLen)
            {
                maxLen = p[i] - 1;
                center = i;
            }
        int start = (center - maxLen) / 2;
        return s.substr(start, maxLen);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    Solution sol;
    cin >> s;
    cout << sol.longestPalindrome(s) << '\n';
    return 0;
}