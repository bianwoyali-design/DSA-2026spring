#include <cstdlib>
#include <iostream>
#include <vector>

class Solution {
public:
  auto minCostConnectPoints(std::vector<std::vector<int>> &points) -> int {
    int n = points.size();
    std::vector matrix(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        int xi = points[i][0], yi = points[i][1];
        int xj = points[j][0], yj = points[j][1];
        matrix[i][j] = matrix[j][i] = std::abs(xi - xj) + std::abs(yi - yj);
      }
    }

    int total_dist = 0;
    std::vector<int> min_dist(n, 0x3f3f3f3f);
    std::vector<bool> visited(n, false);
    min_dist[0] = 0;

    for (int step = 0; step < n; ++step) {
      int current = -1;

      for (int i = 0; i < n; ++i) {
        if (!visited[i] && (current == -1 || min_dist[i] < min_dist[current])) {
          current = i;
        }
      }

      visited[current] = true;
      total_dist += min_dist[current];

      for (int i = 0; i < n; ++i) {
        if (!visited[i] && matrix[current][i] < min_dist[i]) {
          min_dist[i] = matrix[current][i];
        }
      }
    }
    
    return total_dist;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::vector<std::vector<int>> points = {{-1000000, -1000000},
                                          {1000000, 1000000}};
  Solution sol;
  std::cout << sol.minCostConnectPoints(points) << '\n';
}