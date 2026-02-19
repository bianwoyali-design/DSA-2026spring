#include <iostream>
#include <vector>
#include <ranges>
using namespace std;

class Solution
{
public:
    int countBinarySubstrings(const string &s)
    {
        int res = 0, ll = 0, cur = 0;
        char last = s.front();

        for (auto ch : s)
        {
            if (ch == last)
                ++cur;
            else
            {
                last = ch;
                res += min(ll, cur);
                ll = cur;
                cur = 1;
            }
        }

        return res + min(ll, cur);
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    string s = "00110011";
    cout << sol.countBinarySubstrings(s) << '\n';
    return 0;
}