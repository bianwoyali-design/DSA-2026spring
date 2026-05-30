#include <algorithm>
#include <cmath>
#include <iostream>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string str;
  std::cin >> str;
  std::reverse(str.begin(), str.end());

  int ans = 0;
  for (int i = 0; i < str.size(); ++i) {
    ans += static_cast<int>(str[i] - 'A' + 1) * std::pow(26, i);
  }

  std::cout << ans << '\n';
}