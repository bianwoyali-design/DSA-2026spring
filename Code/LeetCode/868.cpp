#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int binaryGap(int n)
    {
        int last = -1, ans = 0;
        for (int i = 0; n; ++i)
        {
            if (n & 1)
            {
                if (last != -1)
                    ans = max(ans, i - last);
                last = i;
            }
            n >>= 1;
        }

        return ans;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    cout << sol.binaryGap(22) << '\n';
    return 0;
}