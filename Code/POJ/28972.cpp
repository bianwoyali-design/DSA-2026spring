#include <array>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;
  std::vector grid(n, std::vector<int>(m, 0));
  for (auto &row : grid) {
    for (auto &x : row) {
      std::cin >> x;
    }
  }

  constexpr static int INF = 1e9;
  constexpr static std::array<std::array<int, 2>, 4> dir = {
      {{{0, 1}}, {{1, 0}}, {{0, -1}}, {{-1, 0}}}};

  std::vector dist(n, std::vector<int>(m, INF));
  std::priority_queue<std::tuple<int, int, int>,
                      std::vector<std::tuple<int, int, int>>, std::greater<>>
      pq;
  pq.emplace(0, 0, 0);
  dist[0][0] = 0;

  while (!pq.empty()) {
    auto [d, x, y] = pq.top();
    pq.pop();

    if (x == n - 1 && y == m - 1) {
      std::cout << d << '\n';
      return 0;
    }

    if (d != dist[x][y]) {
      continue;
    }

    for (int i = 0; i < 4; ++i) {
      int nx = x + dir[i][0];
      int ny = y + dir[i][1];

      if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
        continue;
      }

      int nd = std::max(std::abs(grid[nx][ny] - grid[x][y]), d);
      if (nd < dist[nx][ny]) {
        dist[nx][ny] = nd;
        pq.emplace(dist[nx][ny], nx, ny);
      }
    }
  }
}