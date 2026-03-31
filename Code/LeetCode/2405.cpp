#include <iostream>

class Solution {
public:
  auto partitionString(const std::string& s) -> int {
    int ans = 1, vis = 0;
    for (const char c : s) {
      if ((vis >> (c & 31) & 1) > 0) {
        vis = 0;
        ++ans;
      }
      vis |= 1 << (c & 31);
    }
    return ans;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  auto sol = new Solution;
  std::string s = "ssssss";
  std::cout << sol->partitionString(s) << '\n';
}