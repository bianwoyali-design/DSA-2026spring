#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string s;
  std::cin >> s;
  int maxLen = 0;
  int left = 0;
  std::vector<int> last(26, -1);
  for (int right = 0; right < s.length(); ++right) {
    int char_idx = s[right] - 'a';
    if (last[char_idx] >= left)
      left = last[char_idx] + 1;

    last[char_idx] = right;
    maxLen = std::max(maxLen, right - left + 1);
  }

  std::cout << maxLen << '\n';
  return 0;
}