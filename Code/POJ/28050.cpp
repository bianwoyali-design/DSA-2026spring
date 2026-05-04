#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <vector>

class Warnsdorff {
private:
  int n{};
  int size{};
  std::bitset<19 * 19> visited;
  std::vector<std::vector<int>> g{};

  constexpr static std::array<std::array<int, 2>, 8> dist = {{{{-2, -1}},
                                                              {{-2, 1}},
                                                              {{-1, -2}},
                                                              {{-1, 2}},
                                                              {{1, -2}},
                                                              {{1, 2}},
                                                              {{2, -1}},
                                                              {{2, 1}}}};

  auto _get_id(int row, int col) -> int { return row * n + col; }

  auto _is_valid(int row, int col) -> bool {
    return row >= 0 && row < n && col >= 0 && col < n;
  }

  auto _make_graph() -> void {
    for (int row = 0; row < n; ++row) {
      for (int col = 0; col < n; ++col) {
        for (const auto &[dr, dc] : dist) {
          const int next_row = row + dr;
          const int next_col = col + dc;
          if (_is_valid(next_row, next_col)) {
            g[_get_id(row, col)].emplace_back(_get_id(next_row, next_col));
          }
        }
      }
    }
  }

  auto _get_degree(int node) -> int {
    int count = 0;
    for (auto &&v : g[node]) {
      if (!visited[v]) {
        ++count;
      }
    }
    return count;
  }

public:
  Warnsdorff(int n) : n(n), size(n * n), g(size) { _make_graph(); }

  auto check(int node, int count) -> bool {
    if (count == size) {
      return true;
    }

    std::vector<int> candidates;
    candidates.reserve(g[node].size());
    for (int v : g[node]) {
      if (!visited[v]) {
        candidates.emplace_back(v);
      }
    }

    std::sort(candidates.begin(), candidates.end(), [&](int a, int b) -> bool {
      return _get_degree(a) < _get_degree(b);
    });

    for (int next : candidates) {
      visited[next] = true;
      if (check(next, count + 1)) {
        return true;
      }
      visited[next] = false;
    }

    return false;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n = 0;
  std::cin >> n;
  int sr = 0, sc = 0;
  std::cin >> sr >> sc;

  auto g = Warnsdorff(n);
  std::cout << (g.check(sr * n + sc, 1) ? "success\n" : "fail\n");
}
