#include <algorithm>
#include <set>
#include <vector>
#include <iostream>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, k;
  std::cin >> n >> k;

  constexpr static int max_candidate = 314159;

  std::vector<std::pair<int, int>> votes(n);
  for (auto &[time, candidate] : votes) {
    std::cin >> time >> candidate;
  }

  std::vector<int> s(k);
  std::vector<bool> inset(max_candidate + 1, false);
  std::multiset<int> inside;
  std::multiset<int> outside;
  for (auto &x : s) {
    std::cin >> x;
    inset[x] = true;
    inside.insert(0);
  }

  for (int i = 0; i < max_candidate - k; ++i) {
    outside.insert(0);
  }

  std::sort(votes.begin(), votes.end());
  std::vector<int> count(max_candidate + 1, 0);
  long long ans = 0;

  auto is_good = [&]() -> bool {
    if (outside.empty()) {
      return true;
    }
    return *outside.rbegin() < *inside.begin();
  };

  if (is_good()) {
    ans += votes.front().first;
  }

  for (int i = 0; i < n;) {
    int curr = votes[i].first;

    while (i < n && curr == votes[i].first) {
      int candiate = votes[i].second;

      if (inset[candiate]) {
        auto it = inside.find(count[candiate]);
        inside.erase(it);
        ++count[candiate];
        inside.insert(count[candiate]);
      } else {
        auto it = outside.find(count[candiate]);
        outside.erase(it);
        ++count[candiate];
        outside.insert(count[candiate]);
      }

      ++i;
    }

    if (i < n) {
      int next = votes[i].first;

      if (is_good()) {
        ans += next - curr;
      }
    }
  }

  std::cout << ans << '\n';
}
