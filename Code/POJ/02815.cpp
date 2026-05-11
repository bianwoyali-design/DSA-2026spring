#include <array>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n = 0, m = 0;
  std::cin >> n >> m;
  std::vector matrix(n, std::vector<int>(m));
  for (auto &&row : matrix) {
    for (int &x : row) {
      std::cin >> x;
    }
  }

  const std::array<std::array<int, 2>, 4> dist = {
      {{{0, -1}}, {{-1, 0}}, {{0, 1}}, {{1, 0}}}};
  std::vector visited(n, std::vector<bool>(m, false));

  auto dfs = [&](auto &&self, int x, int y) -> int {
    if (x < 0 || x >= n || y < 0 || y >= m || visited[x][y]) {
      return 0;
    }

    visited[x][y] = true;
    int size = 1;

    for (int i = 0; i < 4; ++i) {
      if (!(matrix[x][y] & (1 << i))) {
        size += self(self, x + dist[i][0], y + dist[i][1]);
      }
    }

    return size;
  };

  int max_size = 0;
  int counts = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (!visited[i][j]) {
        max_size = std::max(max_size, dfs(dfs, i, j));
        ++counts;
      }
    }
  }

  std::cout << counts << '\n' << max_size << '\n';
}