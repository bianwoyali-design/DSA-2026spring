#include <iostream>
#include <vector>
using namespace std;

class NumMatrix
{
    vector<vector<int>> sum;

public:
    NumMatrix(vector<vector<int>> &matrix)
    {
        int n = matrix.size(), m = matrix[0].size();
        sum.resize(n + 1, vector<int>(m + 1));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                sum[i + 1][j + 1] = sum[i + 1][j] + sum[i][j + 1] - sum[i][j] + matrix[i][j];
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        return sum[row2 + 1][col2 + 1] - sum[row2 + 1][col1] - sum[row1][col2 + 1] + sum[row1][col1];
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    vector<vector<int>> matrix = {{3, 0, 1, 4, 2}, {5, 6, 3, 2, 1}, {1, 2, 0, 1, 5}, {4, 1, 0, 1, 7}, {1, 0, 3, 0, 5}};
    NumMatrix *numMatrix = new NumMatrix(matrix);
    cout << numMatrix->sumRegion(2, 1, 4, 3) << '\n'; // return 8 (红色矩形框的元素总和)
    cout << numMatrix->sumRegion(1, 1, 2, 2) << '\n'; // return 11 (绿色矩形框的元素总和)
    cout << numMatrix->sumRegion(1, 2, 2, 4) << '\n'; // return 12 (蓝色矩形框的元素总和)
    return 0;
}