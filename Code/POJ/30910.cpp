#include <iostream>
#include <queue>
#include <vector>

auto dijkstra(int start,
              const std::vector<std::vector<std::pair<int, int>>> &adj) -> int {
  int n = adj.size();
  constexpr static int INF = 1e9;
  std::vector<int> dist(n, INF);
  dist[start] = 0;
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<>>
      pq;
  pq.emplace(0, start);

  while (!pq.empty()) {
    auto [du, u] = pq.top();
    pq.pop();
    if (du > dist[u])
      continue;
    for (auto [v, weight] : adj[u]) {
      if (dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pq.emplace(dist[v], v);
      }
    }
  }

  int time = 0;
  for (int i = 1; i < n; ++i) {
    time += dist[i];
  }
  return time;
}

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;
  std::vector adj1(n, std::vector<std::pair<int, int>>());
  std::vector adj2(n, std::vector<std::pair<int, int>>());
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    --u, --v;
    adj1[u].emplace_back(v, w);
    adj2[v].emplace_back(u, w);
  }

  int time = 0;
  time += dijkstra(0, adj1);
  time += dijkstra(0, adj2);

  std::cout << time << '\n';
}