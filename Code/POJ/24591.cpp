#include <cctype>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

constexpr auto precedence(char op) -> int {
  if (op == '+' || op == '-')
    return 1;
  if (op == '*' || op == '/')
    return 2;
  return 0;
}

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;

  while (n--) {
    std::string s;
    std::cin >> s;

    int l = static_cast<int>(s.length());

    std::stack<char> ops;
    std::vector<std::string> RPN;

    std::string num = "";
    for (int i = 0; i < l; ++i) {
      char c = s[i];

      if (std::isdigit(c) || c == '.')
        num += c;
      else {
        if (!num.empty()) {
          RPN.push_back(std::move(num));
          num = "";
        }

        if (c == '(')
          ops.push(c);
        else if (c == ')') {
          while (!ops.empty()) {
            if (ops.top() == '(') {
              ops.pop();
              break;
            }
            RPN.emplace_back(1, ops.top());
            ops.pop();
          }
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
          while (!ops.empty() && precedence(c) <= precedence(ops.top())) {
            RPN.emplace_back(1, ops.top());
            ops.pop();
          }
          ops.push(c);
        }
      }
    }

    if (!num.empty())
      RPN.push_back(num);

    while (!ops.empty()) {
      RPN.emplace_back(1, ops.top());
      ops.pop();
    }

    for (const auto &s : RPN)
      std::cout << s << ' ';
    std::cout << '\n';
  }
}
