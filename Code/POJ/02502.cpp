#include <cmath>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

auto get_time(const std::pair<int, int> &a, const std::pair<int, int> &b,
              double v) -> double {
  return sqrt((a.first - b.first) * (a.first - b.first) +
              (a.second - b.second) * (a.second - b.second)) /
         (v * 1000.0 / 60.0);
}

auto dijkstra(int start,
              const std::vector<std::vector<std::pair<int, double>>> &g)
    -> int {
  int n = g.size();

  constexpr static double INF = 4e18;
  std::vector<double> dist(n, INF);
  std::priority_queue<std::pair<double, int>,
                      std::vector<std::pair<double, int>>, std::greater<>>
      pq;
  pq.emplace(0.0, start);
  dist[start] = 0.0;

  while (!pq.empty()) {
    auto [du, u] = pq.top();
    pq.pop();

    if (du != dist[u]) {
      continue;
    }

    for (auto [v, weight] : g[u]) {
      if (dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pq.emplace(dist[v], v);
      }
    }
  }

  return round(dist[1]);
}

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int src_x, src_y, tgt_x, tgt_y;
  std::cin >> src_x >> src_y >> tgt_x >> tgt_y;

  std::vector<std::vector<int>> subway_line;
  std::vector<std::pair<int, int>> coordinates;
  coordinates.emplace_back(src_x, src_y);
  coordinates.emplace_back(tgt_x, tgt_y);

  int x, y;
  while (std::cin >> x >> y) {
    if (x == -1 && y == -1) {
      break;
    }

    std::vector<int> line;
    coordinates.emplace_back(x, y);
    line.emplace_back(coordinates.size() - 1);
    while (std::cin >> x >> y && x != -1 && y != -1) {
      coordinates.emplace_back(x, y);
      line.emplace_back(coordinates.size() - 1);
    }

    subway_line.emplace_back(line);
  }

  int n = coordinates.size();
  std::vector g(n, std::vector<std::pair<int, double>>());
  for (auto &line : subway_line) {
    for (int i = 1; i < line.size(); ++i) {
      int u = line[i - 1], v = line[i];
      double dist = get_time(coordinates[u], coordinates[v], 40.0);
      g[u].emplace_back(v, dist);
      g[v].emplace_back(u, dist);
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      double dist = get_time(coordinates[i], coordinates[j], 10.0);
      g[i].emplace_back(j, dist);
      g[j].emplace_back(i, dist);
    }
  }

  std::cout << dijkstra(0, g) << '\n';
}