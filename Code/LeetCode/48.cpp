#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    void rotate(vector<vector<int>> &matrix)
    {
        int n = matrix.size();

        for (int i = 0; i < n; i++)
            for (int j = i; j < n; j++)
                swap(matrix[i][j], matrix[j][i]);

        for (int i = 0; i < n; i++)
            reverse(matrix[i].begin(), matrix[i].end());
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    sol.rotate(matrix);
    for (const auto &m : matrix)
    {
        for (const auto &a : m)
            cout << a << ' ';
        cout << '\n';
    }
    return 0;
}