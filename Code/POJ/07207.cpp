#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<vector<int>> buildMagicSquare(int n)
    {
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        int x = 0, y = n / 2;
        for (int i = 1; i <= n * n; ++i)
        {
            matrix[x][y] = i;
            if (x == 0 && y == n - 1)
                x = (x + n + 1) % n;
            else
            {
                if (matrix[(x + n - 1) % n][(y + n + 1) % n] != 0)
                    x = (x + n + 1) % n;
                else
                    x = (x + n - 1) % n, y = (y + n + 1) % n;
            }
        }

        return matrix;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    int n;
    cin >> n;
    for (const auto &m : sol.buildMagicSquare(2 * n - 1))
    {
        for (const auto &v : m)
            cout << v << ' ';
        cout << '\n';
    }
    return 0;
}