#include <iostream>
#include <cmath>
using namespace std;

class Solution
{
public:
    int countMonobit(int n)
    {
        int monobit = 1;
        int ans = 1;
        while (monobit <= n)
        {
            ++ans;
            monobit = (monobit << 1) | 1;
        }

        return ans;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    cout << sol.countMonobit(1000);
    return 0;
}