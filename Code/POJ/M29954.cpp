#include <iostream>
#include <queue>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int R, C, K;
  std::cin >> R >> C >> K;
  std::vector<std::vector<char>> p(R, std::vector<char>(C));

  int sx, sy, dx, dy;
  for (int i = 0; i < R; ++i)
    for (int j = 0; j < C; ++j) {
      std::cin >> p[i][j];
      if (p[i][j] == 'S')
        sx = i, sy = j;
      if (p[i][j] == 'E')
        dx = i, dy = j;
    }

  std::vector<std::vector<std::vector<int>>> visited(
      R, std::vector<std::vector<int>>(C, std::vector<int>(K + 1, -1)));

  std::queue<std::pair<std::pair<int, int>, int>> q;
  q.push({{sx, sy}, K});
  visited[sx][sy][K] = 0;

  int dict[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

  while (!q.empty()) {
    auto [x, y] = q.front().first;
    int k = q.front().second;
    q.pop();

    if (dx == x && dy == y) {
      std::cout << visited[x][y][k] << '\n';
      return 0;
    }

    for (auto &i : dict) {
      int newX = x + i[0], newY = y + i[1];

      if (newX >= 0 && newX < R && newY >= 0 && newY < C) {
        char c = p[newX][newY];
        int next_k = k;
        if (c == '#') {
          if (next_k > 0)
            --next_k;
          else
            continue;
        }

        if (visited[newX][newY][next_k] == -1) {
          q.push({{newX, newY}, next_k});
          visited[newX][newY][next_k] = visited[x][y][k] + 1;
        }
      }
    }
  }

  std::cout << -1 << '\n';
  return 0;
}