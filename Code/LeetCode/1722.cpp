#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>

class Solution {
  std::vector<int> pa;
  std::vector<int> rank;

  auto Find(int x) -> int { return pa[x] == x ? x : pa[x] = Find(pa[x]); }

  auto Union(int i, int j) -> void {
    int irep = Find(i);
    int jrep = Find(j);

    if (rank[irep] > rank[jrep]) {
      pa[jrep] = irep;
    } else if (rank[irep] < rank[jrep]) {
      pa[irep] = jrep;
    } else {
      pa[irep] = jrep;
      ++rank[jrep];
    }
  }

public:
  auto minimumHammingDistance(std::vector<int> &source,
                              std::vector<int> &target,
                              std::vector<std::vector<int>> &allowedSwaps)
      -> int {
    const int n = source.size();
    rank.resize(n, 0);
    pa.resize(n);
    for (int i = 0; i < n; ++i) {
      pa[i] = i;
    }

    for (auto &&pair : allowedSwaps) {
      Union(pair[0], pair[1]);
    }

    std::vector<std::vector<int>> src(n);
    for (auto &&[i, v] : std::views::zip(std::views::iota(0), source)) {
      int root = Find(i);
      src[root].push_back(v);
    }

    std::vector<std::vector<int>> tgt(n);
    for (auto &&[i, v] : std::views::zip(std::views::iota(0), target)) {
      int root = Find(i);
      tgt[root].push_back(v);
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
      if (src[i].empty())
        continue;

      std::ranges::sort(src[i]);
      std::ranges::sort(tgt[i]);

      std::vector<int> diff;
      std::ranges::set_symmetric_difference(src[i], tgt[i],
                                                   std::back_inserter(diff));

      res += diff.size() / 2;
    }

    return res;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::vector<int> source = {1, 2, 3, 4}, target = {2, 1, 4, 5};
  std::vector<std::vector<int>> allowedSwaps = {{0, 1}, {2, 3}};
  Solution sol;
  std::cout << sol.minimumHammingDistance(source, target, allowedSwaps) << '\n';
}