#include <array>
#include <deque>
#include <iostream>
#include <limits>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  long long h;
  std::array<int, 3> step;
  std::cin >> h;
  for (int i = 0; i < 3; ++i) {
    std::cin >> step[i];
  }

  int mod = std::min({step[0], step[1], step[2]});
  int start = 1 % mod;

  std::vector<long long> dist(mod, std::numeric_limits<long long>::max());
  dist[start] = 1;

  std::deque<int> q;
  std::vector<bool> inqueue(mod, false);
  q.emplace_back(start);
  while (!q.empty()) {
    int u = q.front();
    q.pop_front();
    inqueue[u] = false;

    for (auto w : step) {
      int v = (u + w) % mod;
      if (dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
        if (!inqueue[v]) {
          if (!q.empty() && dist[v] < dist[q.front()]) {
            q.emplace_front(v);
          } else {
            q.emplace_back(v);
          }
          inqueue[v] = true;
        }
      }
    }
  }

  long long ans = 0;
  for (int r = 0; r < mod; ++r) {
    if (h > dist[r]) {
      ans += (h - dist[r]) / mod + 1;
    }
  }

  std::cout << ans << '\n';
}