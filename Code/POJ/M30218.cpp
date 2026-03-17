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

    bool flag = true;
    while (flag && v < 0 && !st.empty() && st.back() > 0) {
      if (st.back() < -v)
        v = st.back() + v, st.pop_back();
      else if (st.back() == -v)
        st.pop_back(), flag = false;
      else
        st.back() += v, flag = false;
    }

    if (flag)
      st.push_back(v);
  }

  std::cout << st.size() << '\n';

  for (const auto &a : st)
    std::cout << a << ' ';
  return 0;
}