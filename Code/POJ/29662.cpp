#include <array>
#include <iostream>
#include <queue>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;
  std::vector grid(n, std::vector<int>(m));
  for (auto &&row : grid) {
    for (auto &&x : row) {
      std::cin >> x;
    }
  }

  constexpr static std::array<std::array<int, 2>, 4> dir = {
      {{{0, 1}}, {{1, 0}}, {{0, -1}}, {{-1, 0}}}};

  std::queue<std::pair<int, int>> q;
  std::vector visited(n, std::vector<bool>(m, false));
  for (auto i : {0, n - 1}) {
    for (int j = 0; j < m; ++j) {
      if (grid[i][j]) {
        visited[i][j] = true;
        q.emplace(i, j);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    for (auto j : {0, m - 1}) {
      if (grid[i][j]) {
        visited[i][j] = true;
        q.emplace(i, j);
      }
    }
  }

  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();

    for (int i = 0; i < 4; ++i) {
      int nx = x + dir[i][0];
      int ny = y + dir[i][1];

      if (nx < 0 || nx >= n || ny < 0 || ny >= m || visited[nx][ny] || !grid[nx][ny]) {
        continue;
      }

      q.emplace(nx, ny);
      visited[nx][ny] = true;
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cout << (visited[i][j] ? 1 : 0) << " \n"[j + 1 == m];
    }
  }
}