#include <array>
#include <iostream>
#include <vector>

class Solution {
  int p, q;
  int cells;
  int all;
  std::vector<int> path;

  constexpr static std::array<std::array<int, 2>, 8> dist = {{{{-2, -1}},
                                                              {{-2, 1}},
                                                              {{-1, -2}},
                                                              {{-1, 2}},
                                                              {{1, -2}},
                                                              {{1, 2}},
                                                              {{2, -1}},
                                                              {{2, 1}}}};

  inline auto dfs(const int state) -> bool {
    int pos = state & 31;
    int remain = state >> 5;

    if (!remain) {
      return true;
    }

    const int curra = pos / q + 1;
    const int currb = pos % q;
    for (int i = 0; i < 8; ++i) {
      const int nxta = curra + dist[i][1];
      const int nxtb = currb + dist[i][0];
      const int nxt = (nxta - 1) * q + nxtb;
      if (nxta >= 1 && nxta <= p && nxtb >= 0 && nxtb < q &&
          (remain & (1 << nxt))) {
        path.push_back(nxt);
        if (dfs((remain & ~(1 << nxt)) << 5 | nxt)) {
          return true;
        }
        path.pop_back();
      }
    }

    return false;
  }

public:
  auto input() -> void {
    std::cin >> p >> q;
    cells = p * q;
    all = (1 << cells) - 1;
  }

  auto output() -> void {
    int start_pos = 0;
    path.clear();
    path.push_back(start_pos);

    if (dfs(((all & ~(1 << start_pos)) << 5) | start_pos)) {
      for (int pos : path) {
        int a = pos / q + 1;
        int b = pos % q;
        std::cout << char('A' + b) << a;
      }
      std::cout << "\n\n";
    } else {
      std::cout << "impossible\n\n";
    }
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;

  Solution sol;
  for (int i = 1; i <= n; ++i) {
    sol.input();
    std::cout << "Scenario #" << i << ":\n";
    sol.output();
  }
}