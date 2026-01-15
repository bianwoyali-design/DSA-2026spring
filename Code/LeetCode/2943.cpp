#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

class Solution
{
public:
    int maximizeSquareHoleArea(int n, int m, vector<int> &hBars, vector<int> &vBars)
    {
        ranges::sort(hBars);
        ranges::sort(vBars);

        int maxh = 1, maxv = 1;
        int currh = 1, currv = 1;
        for (int i = 1; i < hBars.size(); ++i)
            if (hBars[i - 1] + 1 == hBars[i])
                currh++, maxh = max(currh, maxh);
            else
                currh = 1;
        for (int i = 1; i < vBars.size(); ++i)
            if (vBars[i - 1] + 1 == vBars[i])
                currv++, maxv = max(currv, maxv);
            else
                currv = 1;

        return (min(maxh, maxv) + 1) * (min(maxh, maxv) + 1);
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int n = 2, m = 3;
    vector<int> hBars = {2, 3}, vBars = {2, 4};
    Solution sol;
    cout << sol.maximizeSquareHoleArea(n, m, hBars, vBars) << '\n';
    return 0;
}