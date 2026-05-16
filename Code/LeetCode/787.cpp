#include <iostream>
#include <vector>

class Solution {
public:
  auto findCheapestPrice(int n, std::vector<std::vector<int>> &flights, int src,
                         int dst, int k) -> int {
    std::vector<int> dist(n, INT_MAX / 2);
    dist[src] = 0;

    for (int i = 0; i < k + 1; ++i) {
      auto prev = dist;

      for (auto &edge : flights) {
        int u = edge[0], v = edge[1], w = edge[2];
        if (dist[v] > prev[u] + w) {
          dist[v] = prev[u] + w;
        }
      }
    }

    return dist[dst] == INT_MAX / 2 ? -1 : dist[dst];
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n = 4;
  std::vector<std::vector<int>> flights = {
      {0, 1, 100}, {1, 2, 100}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200}};
  int src = 0, dst = 3, k = 1;
  Solution sol;
  std::cout << sol.findCheapestPrice(n, flights, src, dst, k) << '\n';
}