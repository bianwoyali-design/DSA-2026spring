#include <iostream>
#include <algorithm>
#include <ranges>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<int> sortByBits(vector<int> &arr)
    {
        vector<int> bit(10001, 0);
        for (int i = 0; i < 10001; ++i)
            bit[i] = bit[i >> 1] + (i & 1);

        ranges::sort(arr, [&](int x, int y)
                     {
            if (bit[x] < bit[y])
                return true;
            if (bit[x] > bit[y])
                return false;
            return x < y; });

        return arr;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    vector<int> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    for (auto a : sol.sortByBits(arr))
        cout << a << ' ';
    return 0;
}