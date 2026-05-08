#include <iostream>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  std::cin >> t;

  while (t--) {
    std::string n;
    int k;
    std::cin >> n >> k;

    for (int i = 0; i < k; ++i) {
      bool flag = false;
      for (int j = 0; j < n.length() - 1; ++j) {
        if (n[j] > n[j + 1]) {
          n.erase(n.begin() + j);
          flag = true;
          break;
        }
      }
      if (!flag) {
        n.pop_back();
      }
    }

    std::cout << n << '\n';
  }
}