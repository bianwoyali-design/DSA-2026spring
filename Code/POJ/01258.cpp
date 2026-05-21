#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int N{};
  while (std::cin >> N) {
    std::vector matrix(N, std::vector<int>(N));
    for (auto &&row : matrix) {
      for (auto &v : row) {
        std::cin >> v;
      }
    }


    int total_weight = 0;
    std::vector<int> min_dist(N, 0x3f3f3f3f);
    std::vector<bool> visited(N, false);
    min_dist[0] = 0;

    for (int step = 0; step < N; ++step) {
      int current = -1;

      for (int i = 0; i < N; ++i) {
        if (!visited[i] && (current == -1 || min_dist[i] < min_dist[current])) {
          current = i;
        }
      }

      visited[current] = true;
      total_weight += min_dist[current];

      for (int i = 0; i < N; ++i) {
        if (!visited[i] && matrix[current][i] < min_dist[i]) {
          min_dist[i] = matrix[current][i];
        }
      }
    }

    std::cout << total_weight << '\n';
  }
}