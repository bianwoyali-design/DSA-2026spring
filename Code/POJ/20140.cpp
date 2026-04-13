#include <cctype>
#include <iostream>
#include <stack>
#include <string>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string s;
  std::cin >> s;

  std::stack<int> counts;
  std::stack<std::string> st;
  std::string cur;

  for (std::size_t i = 0; i < s.size(); ++i) {
    char ch = s[i];
    if (ch == '[') {
      int num = 0;
      while (++i < s.size() && std::isdigit(static_cast<unsigned char>(s[i]))) {
        num = num * 10 + s[i] - '0';
      }
      counts.emplace(num);
      st.emplace(cur);
      cur.clear();
      --i;
    } else if (ch == ']') {
      int rep = counts.top();
      counts.pop();

      std::string prev = std::move(st.top());
      st.pop();

      std::string segment = cur;
      cur.clear();
      cur.reserve(prev.size() + segment.size() * static_cast<std::size_t>(rep));
      cur += prev;
      while (rep-- > 0) {
        cur += segment;
      }
    } else {
      cur += ch;
    }
  }

  std::cout << cur << '\n';
}