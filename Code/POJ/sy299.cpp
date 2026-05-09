#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Node {
  int num;
  char op;
  bool is_op;
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string expr;
  std::getline(std::cin, expr);

  std::unordered_map<char, int> priority = {
      {'+', 0}, {'-', 0}, {'*', 1}, {'/', 1}};

  std::vector<Node> post_prefix;
  std::vector<char> op_stack;
  for (char c : expr) {
    if (c == ' ') {
      continue;
    } else if (std::isdigit(c)) {
      post_prefix.emplace_back(Node{c - '0', 0, false});
    } else {
      while (!op_stack.empty() && priority[c] <= priority[op_stack.back()]) {
        post_prefix.emplace_back(Node{0, op_stack.back(), true});
        op_stack.pop_back();
      }
      op_stack.emplace_back(c);
    }
  }
  while (!op_stack.empty()) {
    post_prefix.emplace_back(Node{0, op_stack.back(), true});
    op_stack.pop_back();
  }

  std::vector<double> num_stack;
  for (auto e : post_prefix) {
    if (!e.is_op) {
      num_stack.emplace_back(e.num);
    } else {
      double num2 = num_stack.back();
      num_stack.pop_back();
      double num1 = num_stack.back();
      num_stack.pop_back();

      switch (e.op) {
      case '+':
        num_stack.emplace_back(num1 + num2);
        break;
      case '-':
        num_stack.emplace_back(num1 - num2);
        break;
      case '*':
        num_stack.emplace_back(num1 * num2);
        break;
      case '/':
        num_stack.emplace_back(num1 / num2);
        break;
      default:
        break;
      }
    }
  }

  std::printf("%.2lf\n", num_stack.back());
}