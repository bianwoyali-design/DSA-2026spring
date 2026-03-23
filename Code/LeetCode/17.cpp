#include <array>
#include <iostream>
#include <string_view>
#include <vector>

class Solution {
  constexpr static std::array<std::string_view, 10> alphabet = {
      "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

public:
  auto letterCombinations(const std::string &digits)
      -> std::vector<std::string> {
    int n = static_cast<int>(digits.length());
    std::vector<std::string> ans;

    std::string s(n, 0);
    auto dfs = [&](this auto &&dfs, int i) -> void {
      if (i == n) {
        ans.push_back(s);
        return;
      }

      for (const char c : alphabet[digits[i] - '0']) {
        s[i] = c;
        dfs(i + 1);
      }
    };

    dfs(0);

    return ans;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  auto *sol = new Solution;
  std::string digits = "23";
  for (const auto &s : sol->letterCombinations(digits))
    std::cout << s << ' ';
}