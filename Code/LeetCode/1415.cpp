#include <iostream>
#include <string>

class Solution {
public:
  auto getHappyString(int n, int k) -> std::string {
    if (k > 3 << (n - 1))
      return "";
    std::string ans(n, 'a');
    --k;
    ans[0] += k >> (n - 1);
    for (int i = 1; i < n; ++i) {
      ans[i] += k >> (n - 1 - i) & 1;
      if (ans[i] >= ans[i - 1])
        ++ans[i];
    }

    return ans;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  auto *sol = new Solution;
  int n = 3, k = 9;
  std::cout << sol->getHappyString(n, k) << '\n';
  delete sol;
}