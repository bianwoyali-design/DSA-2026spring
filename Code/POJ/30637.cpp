#include <iostream>
#include <stack>
#include <string>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string s;
  std::getline(std::cin, s);
  std::string ipt;
  while (std::getline(std::cin, ipt)) {
    if (!ipt.empty() && ipt.back() == '\r')
      ipt.pop_back();
    if (s.length() != ipt.length()) {
      std::cout << "NO\n";
      continue;
    }

    std::stack<char> st;
    int i = 0, j = 0;
    while (j < ipt.length()) {
      if (!st.empty() && st.top() == ipt[j]) {
        st.pop();
        ++j;
      } else if (i < s.length()) {
        st.push(s[i]);
        ++i;
      } else {
        break;
      }
    }

    if (j == ipt.length())
      std::cout << "YES\n";
    else
      std::cout << "NO\n";
  }
}