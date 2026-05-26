#include <functional>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m, T;
  std::cin >> n >> m >> T;
  std::vector adj(n, std::vector<std::tuple<int, int, int>>());
  int l = 100, r = 0;
  for (int i = 0; i < m; ++i) {
    int u, v, t, a;
    std::cin >> u >> v >> t >> a;
    --u, --v;
    adj[u].emplace_back(v, t, a);
    adj[v].emplace_back(u, t, a);
    l = std::min(l, a);
    r = std::max(r, a);
  }

  auto check = [&](int x) -> bool {
    constexpr static int INF = 0x3f3f3f3f;
    std::vector dist(n, std::vector<int>(2, INF));
    dist[0][0] = 0;

    std::priority_queue<std::tuple<int, int, int>,
                        std::vector<std::tuple<int, int, int>>, std::greater<>>
        pq;
    pq.emplace(0, 0, 0);

    while (!pq.empty()) {
      auto [t, u, status] = pq.top();
      pq.pop();

      if (t > dist[u][status]) {
        continue;
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