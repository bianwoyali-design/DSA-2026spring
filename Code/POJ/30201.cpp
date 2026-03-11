#include <iostream>
#include <vector>
using namespace std;

constexpr static int INF = 1e9;

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    cin >> n;
    vector<vector<int>> G(n, vector<int>(n));
    for (auto &g : G)
        for (auto &x : g)
            cin >> x;

    int N = 1 << n;
    vector<vector<int>> dp(N, vector<int>(n + 1, INF));
    dp[1][0] = 0;

    for (int mask = 1; mask < N; ++mask)
        for (int u = 0; u < n; ++u)
        {
            if (!(mask & (1 << u)))
                continue;
            if (dp[mask][u] == INF)
                continue;
            for (int v = 0; v < n; ++v)
            {
                if ((mask & (1 << v)))
                    continue;
                dp[mask | (1 << v)][v] = min(dp[mask | (1 << v)][v], dp[mask][u] + G[u][v]);
            }
        }

    int ans = INF;
    for (int i = 1; i < n; ++i)
        ans = min(ans, dp[N - 1][i] + G[i][0]);
    cout << ans << '\n';
    return 0;
}