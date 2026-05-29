#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

auto merge_smallest(const std::vector<int> &a, const std::vector<int> &b)
    -> std::vector<int> {
  int n = a.size();

  std::priority_queue<std::tuple<int, int, int>,
                      std::vector<std::tuple<int, int, int>>, std::greater<>>
      pq;
  for (int i = 0; i < n; ++i) {
    pq.emplace(a[i] + b[0], i, 0);
  }

  std::vector<int> res;
  res.reserve(n);
  while (res.size() < n) {
    auto [sum, i, j] = pq.top();
    pq.pop();

    res.emplace_back(sum);

    if (j + 1 < n) {
      pq.emplace(a[i] + b[j + 1], i, j + 1);
    }
  }

  return res;
}

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int T;
  std::cin >> T;
  while (T--) {
    int m, n;
    std::cin >> m >> n;

    std::vector<int> ans(n);
    for (int &x : ans) {
      std::cin >> x;
    }

    std::sort(ans.begin(), ans.end());

    for (int i = 1; i < m; ++i) {
      std::vector<int> b(n);
      for (int &x : b) {
        std::cin >> x;
      }

      std::sort(b.begin(), b.end());
      ans = merge_smallest(ans, b);
    }

    for (int i = 0; i < n; ++i) {
      std::cout << ans[i] << " \n"[i + 1 == n];
    }
  }
}