#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int maxArea(vector<int> &height)
    {
        int l = 0, r = height.size() - 1;
        int maxa = 0;
        while (l < r)
        {
            int hl = height[l], hr = height[r];
            maxa = max(maxa, min(hl, hr) * (r - l));
            if (hl <= hr)
                ++l;
            else
                --r;
        }
        return maxa;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << sol.maxArea(height) << '\n';
    return 0;
}