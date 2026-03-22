#include <iostream>
#include <vector>

[[nodiscard]] auto get_lps(const std::string &s) -> std::vector<int>;

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int cases = 0;
  while (true) {
    int string_length;
    std::cin >> string_length;
    if (string_length == 0)
      break;

    std::string s;
    std::cin >> s;
    std::vector<int> lps = get_lps(s);

    ++cases;
    std::cout << "Test case #" << cases << '\n';

    for (int length = 2; length <= string_length; ++length) {
      int k = length - lps[length - 1];
      if (length % k == 0 && length / k > 1)
        std::cout << length << ' ' << length / k << '\n';
    }

    std::cout << '\n';
  }
}

auto get_lps(const std::string &s) -> std::vector<int> {
  int n = static_cast<int>(s.length());

  std::vector<int> next(n);
  int length = 0;
  for (int i = 1; i < n; ++i) {
    while (length > 0 && s[i] != s[length])
      length = next[length - 1];
    if (s[i] == s[length])
      ++length;
    next[i] = length;
  }

  return next;
}