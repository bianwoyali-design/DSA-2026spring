#include <iostream>
#include <vector>
using namespace std;

vector<pair<int, int>> dist = {{1, 2}, {2, 1}, {-1, 2}, {-2, 1}, {1, -2}, {2, -1}, {-1, -2}, {-2, -1}};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    cin >> T;
    while (T--)
    {
        int n, m, x, y;
        cin >> n >> m >> x >> y;

        int ans = 0;
        vector<vector<int>> valid(n, vector<int>(m, false));
        auto dfs = [&](this auto &&dfs, int desx, int desy, int steps) -> void // explicit object member function only available with '-std=c++23' or '-std=gnu++23' [-Wc++23-extensions]
        {
            if (steps == n * m)
            {
                ans++;
                return;
            }
            valid[desx][desy] = true;
            for (const auto &xy : dist)
            {
                auto [x, y] = xy;
                int newX = desx + x;
                int newY = desy + y;
                if (newX >= 0 && newX < n && newY >= 0 && newY < m && !valid[newX][newY])
                    dfs(newX, newY, steps + 1);
            }
            valid[desx][desy] = false;
        };

        dfs(x, y, 1);

        cout << ans << '\n';
    }
    return 0;
}