#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;

  constexpr static int INF = 1e9;
  std::vector dist(n, std::vector<int>(n, INF));
  for (int i = 0; i < n; ++i) {
    dist[i][i] = 0;
  }
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    --u, --v;
    dist[u][v] = std::min(dist[u][v], w);
    dist[v][u] = std::min(dist[v][u], w);
  }

  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (dist[i][k] != INF && dist[k][j] != INF) {
          dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
  }

  int total = INF;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      int curr = 0;
      for (int u = 0; u < n; ++u) {
        for (int v = u + 1; v < n; ++v) {
          curr += std::min(
              {dist[u][v], dist[u][i] + dist[j][v], dist[u][j] + dist[i][v]});
        }
      }
      total = std::min(total, curr);
    }
  }

  std::cout << total << '\n';
}