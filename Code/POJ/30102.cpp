#include <algorithm>
#include <iostream>
#include <vector>


auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int N;
  std::cin >> N;

  std::vector<int> h(N);
  for (int i = 0; i < N; ++i)
    std::cin >> h[i];

  std::vector<int> st_max;
  std::vector<int> cand;
  int max_len = 0;

  for (int j = 0; j < N; ++j) {
    while (!st_max.empty() && h[st_max.back()] < h[j]) {
      st_max.pop_back();
    }
    int lj = st_max.empty() ? -1 : st_max.back();

    while (!cand.empty() && h[cand.back()] >= h[j]) {
      cand.pop_back();
    }

    if (!cand.empty()) {
      auto it = std::upper_bound(cand.begin(), cand.end(), lj);
      if (it != cand.end()) {
        int best_i = *it;
        max_len = std::max(max_len, j - best_i + 1);
      }
    }

    st_max.push_back(j);
    cand.push_back(j);
  }

  std::cout << max_len << '\n';
}