#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    long long largestSquareArea(vector<vector<int>> &bottomLeft, vector<vector<int>> &topRight)
    {
        int n = bottomLeft.size();
        int maxSide = 0;

        for (int i = 0; i < n - 1; ++i)
            if (min(topRight[i][0] - bottomLeft[i][0], topRight[i][1] - bottomLeft[i][1]) > maxSide)
                for (int j = i + 1; j < n; ++j)
                {
                    int w = min(topRight[i][0], topRight[j][0]) - max(bottomLeft[i][0], bottomLeft[j][0]);
                    int h = min(topRight[i][1], topRight[j][1]) - max(bottomLeft[i][1], bottomLeft[j][1]);

                    maxSide = max(maxSide, min(w, h));
                }

        return (long long)maxSide * maxSide;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    vector<vector<int>> bottomLeft = {{1, 1}, {2, 2}, {3, 1}}, topRight = {{3, 3}, {4, 4}, {6, 6}};
    Solution sol;
    cout << sol.largestSquareArea(bottomLeft, topRight) << '\n';
    return 0;
}