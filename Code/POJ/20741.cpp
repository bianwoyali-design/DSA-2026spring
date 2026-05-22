#include <array>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n{};
  std::cin >> n;
  std::vector matrix(n, std::string());
  for (auto &&row : matrix) {
    std::cin >> row;
  }

  bool found = false;
  std::queue<std::pair<int, int>> first_island;
  for (int i = 0; i < n && !found; ++i) {
    for (int j = 0; j < n && !found; ++j) {
      if (matrix[i][j] == '1') {
        matrix[i][j] = '2';
        first_island.emplace(i, j);
        found = true;
      }
    }
  }

  constexpr std::array<std::array<int, 2>, 4> dist = {
      {{{0, 1}}, {{1, 0}}, {{0, -1}}, {{-1, 0}}}};

  std::queue<std::pair<int, int>> q;
  while (!first_island.empty()) {
    auto [x, y] = first_island.front();
    first_island.pop();
    q.emplace(x, y);

    for (int i = 0; i < 4; ++i) {
      int newX = x + dist[i][0];
      int newY = y + dist[i][1];
      if (newX >= 0 && newX < n && newY >= 0 && newY < n &&
          matrix[newX][newY] == '1') {
        matrix[newX][newY] = '2';
        first_island.emplace(newX, newY);
      }
    }
  }

  int step = 0;
  while (!q.empty()) {
    int sz = q.size();
    while (sz--) {
      auto [x, y] = q.front();
      q.pop();

      for (int i = 0; i < 4; ++i) {
        int newX = x + dist[i][0];
        int newY = y + dist[i][1];
        if (newX >= 0 && newX < n && newY >= 0 && newY < n && matrix[newX][newY] != '2') {
          if (matrix[newX][newY] == '1') {
            std::cout << step << '\n';
            return 0;
          }

          matrix[newX][newY] = '2';
          q.emplace(newX, newY);
        }
      }
    }
    ++step;
  }
}