#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  long long a, b, c;
  std::cin >> a >> b >> c;

  std::vector<long long> step;
  for (long long x : {a, b, c}) {
    if (x > 0) {
      step.push_back(x);
    }
  }

  if (step.empty()) {
    int q;
    std::cin >> q;
    while (q--) {
      long long tgt;
      std::cin >> tgt;
      std::cout << (tgt == 0 ? "Yes\n" : "No\n");
    }
    return 0;
  }

  int mod = static_cast<int>(*std::min_element(step.begin(), step.end()));
  int start = 0;
  constexpr static long long INF = 4e18;

  std::vector<long long> dist(mod, INF);
  dist[start] = start;
  std::priority_queue<std::pair<long long, int>,
                      std::vector<std::pair<long long, int>>, std::greater<>>
      pq;
  pq.emplace(dist[start], start);

  while (!pq.empty()) {
    auto [du, u] = pq.top();
    pq.pop();

    if (du != dist[u])
      continue;

    for (long long w : step) {
      int v = static_cast<int>((u + w) % mod);
      if (dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        pq.emplace(dist[v], v);
      }
    }
  }

  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    long long tgt;
    std::cin >> tgt;
    int r = static_cast<int>(tgt % mod);
    if (dist[r] != INF && dist[r] <= tgt) {
      std::cout << "Yes\n";
    } else {
      std::cout << "No\n";
    }
  }
}
