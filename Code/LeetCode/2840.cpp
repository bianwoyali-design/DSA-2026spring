#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
  auto checkStrings(const std::string &s1, const std::string &s2) -> bool {
    std::vector count1(2, std::vector<int>(26, 0));
    std::vector count2(2, std::vector<int>(26, 0));
    for (int i = 0; i < s1.length(); ++i) {
      ++count1[i % 2][s1[i] - 'a'];
      ++count2[i % 2][s2[i] - 'a'];
    }
    return count1 == count2;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string s1 = "abcdba", s2 = "cabdab";
  Solution sol;
  std::cout << sol.checkStrings(s1, s2) << '\n';
}