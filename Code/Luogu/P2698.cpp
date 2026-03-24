#include <algorithm>
#include <limits>
#include <print>
#include <iostream>
#include <deque>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int N, D;
  std::cin >> N >> D;

  std::vector<std::pair<int, int>> coordinates(N);
  for (auto &c : coordinates)
    std::cin >> c.first >> c.second;
  std::ranges::sort(coordinates);

  std::deque<int> maxq, minq;

  int l = 0, r = 0;
  int res = std::numeric_limits<int>::max();
  while (r < N) {
    while (!maxq.empty() &&
           coordinates[maxq.back()].second <= coordinates[r].second)
      maxq.pop_back();
    maxq.push_back(r);

    while (!minq.empty() &&
           coordinates[minq.back()].second >= coordinates[r].second)
      minq.pop_back();
    minq.push_back(r);

    while (l <= r && coordinates[maxq.front()].second - coordinates[minq.front()].second >= D) {
      res = std::min(res, coordinates[r].first - coordinates[l].first);
      ++l;
      if (!maxq.empty() && maxq.front() < l)
        maxq.pop_front();
      if (!minq.empty() && minq.front() < l)
        minq.pop_front();
    }
    ++r;
  }

  if (res == std::numeric_limits<int>::max())
    std::println("-1");
  else
    std::println("{}", res);
}