#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int m{}, n{};
  std::cin >> m >> n;
  std::vector matrix(m, std::vector<int>(n));
  for (auto &&row : matrix) {
    for (auto &x : row) {
      std::cin >> x;
    }
  }

  std::vector<int> height(n + 1, 0);
  int res = 0;
  for (auto &&row : matrix) {
    std::vector<int> stack = {-1};

    for (int i = 0; i < n; ++i) {
      if (row[i] == 0) {
        ++height[i];
      } else {
        height[i] = 0;
      }
    }

    for (int i = 0; i <= n; ++i) {
      while (stack.back() != -1 && height[stack.back()] > height[i]) {
        int top = stack.back();
        stack.pop_back();
        res = std::max(res, height[top] * (i - stack.back() - 1));
      }
      stack.push_back(i);
    }
  }

  std::cout << res << '\n';
}