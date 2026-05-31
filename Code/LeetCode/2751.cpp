#include <algorithm>
#include <iostream>
#include <numeric>
#include <print>
#include <stack>
#include <vector>

class Solution {
public:
  auto survivedRobotsHealths(std::vector<int> &positions,
                             std::vector<int> &healths,
                             const std::string &directions)
      -> std::vector<int> {
    int n = positions.size();
    std::vector<int> index(n);
    std::ranges::iota(index, 0);
    std::ranges::sort(index, {}, [&](int i) -> int { return positions[i]; });

    std::stack<int> st;
    for (int i : index) {
      if (directions[i] == 'R') {
        st.emplace(i);
      } else {
        while (!st.empty() && healths[i]) {
          int j = st.top();
          if (healths[j] < healths[i]) {
            st.pop();
            healths[j] = 0;
            --healths[i];
          } else if (healths[j] > healths[i]) {
            healths[i] = 0;
            --healths[j];
          } else {
            st.pop();
            healths[i] = healths[j] = 0;
          }
        }
      }
    }

    std::vector<int> res;
    for (auto h : healths) {
      if (h) {
        res.emplace_back(h);
      }
    }

    return res;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  Solution sol;
  std::vector<int> positions = {5, 4, 3, 2, 1}, healths = {2, 17, 9, 15, 10};
  std::string directions = "RRRRR";

  std::println("{}", sol.survivedRobotsHealths(positions, healths, directions));
}