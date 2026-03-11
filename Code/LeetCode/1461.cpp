#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    bool hasAllCodes(string s, int k)
    {
        int total_needed = 1 << k;
        if (s.size() < (size_t)total_needed + k - 1)
            return false;

        vector<bool> seen(total_needed, false);

        int x = 0;
        int cnt = 0;
        int MASK = total_needed - 1;

        for (int i = 0; i < k - 1; ++i)
        {
            x = (x << 1) | (s[i] & 1);
        }

        for (int i = k - 1; i < s.length(); ++i)
        {
            x = ((x << 1) & MASK) | (s[i] & 1);
            if (!seen[x])
            {
                seen[x] = true;
                if (++cnt == total_needed)
                    return true;
            }
        }

        return false;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    string s = "0110";
    int k = 2;
    cout << sol.hasAllCodes(s, k) << '\n';
    return 0;
}