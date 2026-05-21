#include <deque>
#include <iostream>
#include <utility>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m, k;
  std::cin >> n >> m >> k;

  std::vector adj(n + 1, std::vector<std::pair<int, int>>());
  while (m--) {
    int u, v, w;
    std::cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  std::vector<int> terminals(k);
  for (auto &&v : terminals) {
    std::cin >> v;
  }

  std::vector dp(1 << k, std::vector<int>(n + 1, 0x3f3f3f3f));

  for (int i = 0; i < k; ++i) {
    dp[1 << i][terminals[i]] = 0;
  }

  for (int mask = 1; mask < (1 << k); ++mask) {
    for (int sub = (mask - 1) & mask; sub > 0; sub = (sub - 1) & mask) {
      if (sub > (mask ^ sub)) {
        continue;
      }
      for (int i = 1; i <= n; ++i) {
        dp[mask][i] = std::min(dp[mask][i], dp[sub][i] + dp[mask ^ sub][i]);
      }
    }

    std::deque<int> q;
    std::vector<bool> in_queue(n + 1, false);
    for (int i = 1; i <= n; ++i) {
      if (dp[mask][i] != 0x3f3f3f3f) {
        in_queue[i] = true;
        q.emplace_back(i);
      }
    }

    while (!q.empty()) {
      int u = q.front();
      q.pop_front();
      in_queue[u] = false;

      for (auto &&[v, w] : adj[u]) {
        if (dp[mask][v] > dp[mask][u] + w) {
          dp[mask][v] = dp[mask][u] + w;

          if (!in_queue[v]) {
            in_queue[v] = true;

            if (!q.empty() && dp[mask][v] < dp[mask][q.front()]) {
              q.emplace_front(v);
            } else {
              q.emplace_back(v);
            }
          }
        }
      }
    }
  }

  std::cout << dp[(1 << k) - 1][terminals[0]] << '\n';
}