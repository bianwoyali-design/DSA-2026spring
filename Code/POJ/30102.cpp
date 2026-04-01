#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int N;
  std::cin >> N;

  std::vector<int> h(N);
  for (auto &price : h)
    std::cin >> price;

  std::vector<int> L(N, -1);
  std::vector<int> st;

  for (int j = 0; j < N; ++j) {
    while (!st.empty() && h[st.back()] < h[j])
      st.pop_back();
    if (!st.empty())
      L[j] = st.back();
    st.push_back(j);
  }

  int max_len = 0;
  std::vector<int> cand;

  for (int j = 0; j < N; ++j) {
    while (!cand.empty() && h[cand.back()] >= h[j])
      cand.pop_back();

    if (!cand.empty()) {
      int l = 0, r = static_cast<int>(cand.size() - 1);
      int best_i = -1;

      while (l <= r) {
        int mid = l + ((r - l) >> 1);
        if (cand[mid] > L[j]) {
          best_i = cand[mid];
          r = mid - 1;
        } else {
          l = mid + 1;
        }
      }

      if (best_i != -1) {
        int current_len = j - best_i + 1;
        if (current_len > max_len)
          max_len = current_len;
      }
    }

    cand.push_back(j);
  }

  std::cout << max_len << '\n';

  return 0;
}