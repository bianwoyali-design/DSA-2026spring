#include <array>
#include <functional>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  long long T;
  std::cin >> n >> m >> T;
  std::vector adj(n, std::vector<std::tuple<int, long long, int>>());
  for (int i = 0; i < m; ++i) {
    int u, v, a;
    long long t;
    std::cin >> u >> v >> t >> a;
    --u, --v;
    adj[u].emplace_back(v, t, a);
    adj[v].emplace_back(u, t, a);
  }

  auto check = [&](int x) -> bool {
    constexpr static long long INF = 4e18;
    std::vector dist(n, std::array<long long, 2>{INF, INF});
    dist[0][0] = 0;

    std::priority_queue<std::tuple<long long, int, int>,
                        std::vector<std::tuple<long long, int, int>>,
                        std::greater<>>
        pq;
    pq.emplace(0, 0, 0);

    while (!pq.empty()) {
      auto [t, u, status] = pq.top();
      pq.pop();

      if (t != dist[u][status]) {
        continue;
      }
      if (t > T) {
        continue;
      }
      if (u == n - 1) {
        return true;
      }

      for (auto [v, weight, damage] : adj[u]) {
        if (x >= damage) {
          if (dist[v][status] > t + weight) {
            dist[v][status] = t + weight;
            pq.emplace(dist[v][status], v, status);
          }
        } else if (!status) {
          if (dist[v][1] > t + weight) {
            dist[v][1] = t + weight;
            pq.emplace(dist[v][1], v, 1);
          }
        }
      }
    }

    return std::min(dist[n - 1][0], dist[n - 1][1]) <= T;
  };

  int l = 0;
  int r = 100;
  while (l < r) {
    int mid = l + ((r - l) >> 1);
    if (check(mid)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }

  std::cout << l << '\n';
}
