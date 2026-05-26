#include <iostream>
#include <vector>

class Solution {
public:
  auto canReach(const std::string &s, int minJump, int maxJump) -> bool {
    int n = s.length();
    std::vector<bool> dp(n, false);
    dp[0] = true;
    int j = 1;
    for (int i = 0; i < n && j < n; ++i) {
      if (s[i] == '0' && dp[i]) {
        for (j = std::max(j, i + minJump); j <= std::min(i + maxJump, n - 1);
             ++j) {
          dp[j] = true;
        }
      }
    }
    return dp.back() && s.back() == '0';
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string s = "011010";
  int minJump = 2, maxJump = 3;
  Solution sol;
  std::cout << sol.canReach(s, minJump, maxJump) << '\n';
}