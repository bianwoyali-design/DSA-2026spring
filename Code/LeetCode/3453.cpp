#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    double separateSquares(vector<vector<int>> &squares)
    {
        double total = 0, max_y = 0;
        for (const auto &s : squares)
        {
            total += (double)s[2] * s[2];
            max_y = max(max_y, (double)s[1] + s[2]);
        }

        auto check = [&](double curr_y) -> bool
        {
            double lower = 0;
            for (const auto &s : squares)
                if (s[1] < curr_y)
                    lower += s[2] * min((double)s[2], curr_y - s[1]);
            return lower * 2 >= total;
        };

        double l = 0, r = max_y;
        double eps = 1e-5;
        while (abs(l - r) > eps)
        {
            double mid = (l + r) / 2;
            if (check(mid))
                r = mid;
            else
                l = mid;
        }
        return r;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    vector<vector<int>> squares = {{0, 0, 2}, {1, 1, 1}};
    cout << sol.separateSquares(squares) << '\n';
    return 0;
}