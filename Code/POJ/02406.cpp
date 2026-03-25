#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string s;
  while (std::cin >> s) {
    if (s == ".")
      break;

    int n = static_cast<int>(s.length());
    std::vector<int> lps(n, 0);
    int length = 0;
    for (int i = 1; i < n; ++i) {
      while (length > 0 && s[i] != s[length])
        length = lps[length - 1];
      if (s[i] == s[length])
        ++length;
      lps[i] = length;
    }

    int p = n - lps.back();
    if (n % p == 0)
      std::cout << n / p << '\n';
    else
      std::cout << 1 << '\n';
  }
}