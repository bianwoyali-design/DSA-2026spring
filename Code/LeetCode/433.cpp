#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>


class Solution {
public:
  auto minMutation(const std::string &startGene, const std::string &endGene,
                   std::vector<std::string> &bank) -> int {
    const auto n = bank.size();

    int end_idx = -1;
    for (int i = 0; i < n; ++i) {
      if (bank[i] == endGene) {
        end_idx = i;
        break;
      }
    }
    if (end_idx == -1)
      return -1;
    if (startGene == endGene)
      return 0;

    auto bucket = _make_bucket(startGene, bank);

    std::queue<int> q;
    std::vector<bool> visited(n + 1, false);

    q.emplace(n);
    visited[n] = true;
    int steps = 0;
    while (!q.empty()) {
      ++steps;
      int sz = q.size();
      for (int k = 0; k < sz; ++k) {
        auto front = q.front();
        q.pop();

        for (int i = 0; i < 8; ++i) {
          auto pattern = front == n ? startGene : bank[front];
          pattern[i] = '*';
          for (auto &&p : bucket[pattern]) {
            if (!visited[p]) {
              if (p == end_idx)
                return steps;
              visited[p] = true;
              q.emplace(p);
            }
          }
        }
      }
    }

    return -1;
  }

private:
  auto _make_bucket(const std::string &startGene,
                    const std::vector<std::string> &bank)
      -> std::unordered_map<std::string, std::vector<int>> {
    const auto n = bank.size();
    std::unordered_map<std::string, std::vector<int>> res;

    for (int i = 0; i < 8; ++i) {
      auto pattern = startGene;
      pattern[i] = '*';
      res[pattern].emplace_back(n);
    }

    for (int i = 0; i < n; ++i) {
      const auto &gene = bank[i];

      for (int j = 0; j < 8; ++j) {
        auto pattern = gene;
        pattern[j] = '*';
        res[pattern].emplace_back(i);
      }
    }

    return res;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string start = "AAAAACCC";
  std::string end = "AACCCCCC";
  std::vector<std::string> bank = {"AAAACCCC", "AAACCCCC", "AACCCCCC"};

  Solution sol;
  std::cout << sol.minMutation(start, end, bank) << '\n';
}