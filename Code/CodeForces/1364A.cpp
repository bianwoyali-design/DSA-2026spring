#include <cstddef>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  std::cin >> t;

  while (t--) {
    int n, x;
    std::cin >> n >> x;

    std::vector<int> a(n);

    int sum1 = 0, sum2;
    bool flag = false;
    for (int &v : a) {
      std::cin >> v;
      sum1 += v;
      if (v % x != 0)
        flag = true;
    }

    sum2 = sum1;

    if (!flag) {
      std::cout << -1 << '\n';
      continue;
    }

    if (sum1 % x != 0) {
      std::cout << n << '\n';
      continue;
    }

    size_t left = 0, right = n - 1;
    while (left <= right) {
      if (a[left] % x == 0)
        sum1 -= a[left++];
      else {
        std::cout << n - left - 1 << '\n';
        break;
      }

      if (a[right] % x == 0)
        sum2 -= a[right--];
      else {
        std::cout << right << '\n';
        break;
      }
    }
  }
}