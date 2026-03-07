#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int numSteps(string s)
    {
        int ans = 0, n = s.length();
        bool flag = false;
        for (int i = n - 1; i >= 0; --i)
            if (s[i] == '0')
                ans += (flag ? 2 : 1);
            else if (!flag)
            {
                if (i != 0)
                    ans += 2;
                flag = true;
            }
            else
                ++ans;
        return ans;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    cout << sol.numSteps("1") << '\n';
    return 0;
}