#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int N;
  std::cin >> N;
  std::vector<int> st;

  while (N--) {
    int v;
    std::cin >> v;

    if (v < 0) {
      while (!st.empty() && v < 0 && st.back() > 0) {
        v += st.back();
        if (v < 0) {
          st.pop_back();
        } else if (v > 0) {
          st.back() = v;
        } else {
          st.pop_back();
        }
      }
      if (v < 0) {
        st.emplace_back(v);
      }
    } else {
      st.emplace_back(v);
    }
  }

  std::cout << st.size() << '\n';

  for (const auto &a : st)
    std::cout << a << ' ';
  return 0;
}