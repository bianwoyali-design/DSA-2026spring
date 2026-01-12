#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int ans = 0;

void backtrack(vector<vector<char>> &mat, vector<int> &record, int col, int cnt, int k)
{
    if (cnt == k)
    {
        ans++;
        return;
    }
    if (col == mat.size())
        return;
    for (int i = 0; i < mat[col].size(); ++i)
    {
        if (mat[col][i] == '#' && !count(record.begin(), record.end(), i))
        {
            record[col] = i;
            backtrack(mat, record, col + 1, cnt + 1, k);
            record[col] = -1;
        }
    }
    backtrack(mat, record, col + 1, cnt, k);
}

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int n, k;
    while (cin >> n >> k)
    {
        if (n == -1 && k == -1)
            break;
        vector<vector<char>> mat(n, vector<char>(n));
        for (auto &submat : mat)
            for (auto &c : submat)
                cin >> c;
        vector<int> record(n, -1);
        ans = 0;
        backtrack(mat, record, 0, 0, k);
        cout << ans << '\n';
    }
    return 0;
}