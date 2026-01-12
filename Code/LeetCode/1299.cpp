#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<int> replaceElements(vector<int> &arr)
    {
        int maxn = -1;
        for (int i = arr.size() - 1; i >= 0; --i)
        {
            int curr = arr[i];
            arr[i] = maxn;
            maxn = max(maxn, curr);
        }
        return arr;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    vector<int> arr = {17, 18, 5, 4, 6, 1};
    Solution sol;
    vector<int> ans = sol.replaceElements(arr);
    for (const auto &a : ans)
        cout << a << ' ';
    return 0;
}