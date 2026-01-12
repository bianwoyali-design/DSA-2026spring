#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int minTimeToVisitAllPoints(vector<vector<int>> &points)
    {
        int ans = 0;
        for (int i = 1; i < points.size(); ++i)
        {
            int absX = abs(points[i - 1][0] - points[i][0]);
            int absY = abs(points[i - 1][1] - points[i][1]);
            ans += max(absX, absY);
        }
        return ans;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    vector<vector<int>> points = {{3, 2}, {-2, 2}};
    Solution sol;
    cout << sol.minTimeToVisitAllPoints(points) << '\n';
    return 0;
}