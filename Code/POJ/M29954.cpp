#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

int visited[105][105][15];

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int R, C, K;
    cin >> R >> C >> K;
    vector<vector<char>> p(R, vector<char>(C));

    int sx, sy, dx, dy;
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
        {
            cin >> p[i][j];
            if (p[i][j] == 'S')
                sx = i, sy = j;
            if (p[i][j] == 'E')
                dx = i, dy = j;
        }

    memset(visited, -1, sizeof(visited));

    queue<pair<pair<int, int>, int>> q;
    q.push({{sx, sy}, K});
    visited[sx][sy][K] = 0;

    int dict[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    while (!q.empty())
    {
        auto [x, y] = q.front().first;
        int k = q.front().second;
        q.pop();

        if (x == dx && y == dy)
        {
            cout << visited[x][y][k] << '\n';
            return 0;
        }

        for (int i = 0; i < 4; ++i)
        {
            int newX = x + dict[i][0], newY = y + dict[i][1];

            if (newX >= 0 && newX < R && newY >= 0 && newY < C)
            {
                char c = p[newX][newY];
                int next_k = k;
                if (c == '#')
                    if (next_k > 0)
                        --next_k;
                    else
                        continue;

                if (visited[newX][newY][next_k] == -1)
                {
                    q.push({{newX, newY}, next_k});
                    visited[newX][newY][next_k] = visited[x][y][k] + 1;
                }
            }
        }
    }

    cout << -1 << '\n';
    return 0;
}