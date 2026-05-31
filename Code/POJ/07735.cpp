#include <iostream>
#include <queue>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int k, n, r;
  std::cin >> k >> n >> r;

  std::vector g(n, std::vector<std::tuple<int, int, int>>());
  for (int i = 0; i < r; ++i) {
    int s, d, l, t;
    std::cin >> s >> d >> l >> t;
    --s, --d;
    g[s].emplace_back(d, l, t);
  }

  constexpr static int INF = 1e9;
  std::vector dist(n, std::vector<int>(k + 1, INF));
  std::priority_queue<std::tuple<int, int, int>,
                      std::vector<std::tuple<int, int, int>>, std::greater<>>
      pq;
  dist[0][0] = 0;
  pq.emplace(0, 0, 0);

  while (!pq.empty()) {
    auto [du, u, cost] = pq.top();
    pq.pop();

    if (du != dist[u][cost]) {
      continue;
    }

    if (u == n - 1) {
      std::cout << du << '\n';
      return 0;
    }

    for (auto [v, l, t] : g[u]) {
      if (cost + t <= k && dist[v][cost + t] > du + l) {
        dist[v][cost + t] = du + l;
        pq.emplace(dist[v][cost + t], v, cost + t);
      }
    }
  }

  std::cout << -1 << '\n';
}