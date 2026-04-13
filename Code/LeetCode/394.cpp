#include <cctype>
#include <iostream>
#include <stack>
#include <string>

class Solution {
public:
  auto decodeString(const std::string &s) -> std::string {
    std::stack<int> counts;
    std::stack<std::string> results;
    std::string cur;
    int num = 0;

    for (char ch : s) {
      if (std::isdigit(static_cast<unsigned char>(ch))) {
        num = num * 10 + (ch - '0');
      } else if (ch == '[') {
        counts.push(num);
        results.push(cur);
        num = 0;
        cur.clear();
      } else if (ch == ']') {
        int rep = counts.top();
        counts.pop();

        std::string prev = results.top();
        results.pop();

        std::string expanded = "";
        while (rep--)
          expanded += cur;

        cur = std::move(prev) + expanded;
      } else {
        cur += ch;
      }
    }

    return cur;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string s = "3[a2[c]]";
  Solution sol;
  std::cout << sol.decodeString(s) << '\n';
}