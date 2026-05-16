#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n{};
  std::cin >> n;
  std::vector<std::string> location(n);
  for (auto &&loc : location) {
    std::cin >> loc;
  }

  std::vector dist(n, std::vector<int>(n, INT_MAX / 2));
  std::vector next_node(n, std::vector<int>(n, -1));
  for (int i = 0; i < n; ++i) {
    dist[i][i] = 0;
  }

  int m{};
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    std::string a, b;
    int d;
    std::cin >> a >> b >> d;
    int u = std::find(location.begin(), location.end(), a) - location.begin();
    int v = std::find(location.begin(), location.end(), b) - location.begin();

    if (dist[u][v] > d) {
      dist[u][v] = dist[v][u] = d;
      next_node[u][v] = v;
      next_node[v][u] = u;
    }
  }

  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
          next_node[i][j] = next_node[i][k];
        }
      }
    }
  }

  auto print_path = [&](int u, int v) -> std::string {
    std::vector<int> path = {u};
    while (u != v) {
      u = next_node[u][v];
      path.emplace_back(u);
    }

    auto result = location[path.front()];
    for (int i = 1; i < path.size(); ++i) {
      int from = path[i - 1];
      int to = path[i];
      result += "->(" + std::to_string(dist[from][to]) + ")->" + location[to];
    }

    return result;
  };

  int r{};
  std::cin >> r;
  for (int i = 0; i < r; ++i) {
    std::string a, b;
    std::cin >> a >> b;
    int src = std::find(location.begin(), location.end(), a) - location.begin();
    int dst = std::find(location.begin(), location.end(), b) - location.begin();
    std::cout << print_path(src, dst) << '\n';
  }
}