#include <iostream>
#include <string>

class Solution {
public:
  auto generateString(const std::string &str1, const std::string &str2)
      -> std::string {
    int n = str1.size(), m = str2.size();
    std::string res(n + m - 1, '?');

    for (int i = 0; i < n; ++i) {
      if (str1[i] != 'T') {
        continue;
      }

      for (int j = 0; j < m; ++j) {
        char v = res[i + j];
        if (v != '?' && v != str2[j]) {
          return "";
        }
        res[i + j] = str2[j];
      }
    }

    auto prev = res;
    for (auto &c : res) {
      if (c == '?') {
        c = 'a';
      }
    }

    for (int i = 0; i < n; ++i) {
      if (str1[i] != 'F') {
        continue;
      }

      if (std::string(res.begin() + i, res.begin() + i + m) != str2) {
        continue;
      }

      bool flag = false;
      for (int j = i + m - 1; j >= i; --j) {
        if (prev[j] == '?') {
          res[j] = 'b';
          flag = true;
          break;
        }
      }

      if (!flag) {
        return "";
      }
    }

    return res;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string str1 = "TFTF", str2 = "abc";
  Solution sol;
  std::cout << sol.generateString(str1, str2) << '\n';
}