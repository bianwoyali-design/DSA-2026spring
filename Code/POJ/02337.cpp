#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t{};
  std::cin >> t;
  while (t--) {
    int n{};
    std::cin >> n;
    std::vector<std::string> words(n);
    for (auto &&word : words) {
      std::cin >> word;
    }

    std::sort(words.rbegin(), words.rend());

    std::vector adj(26, std::vector<std::pair<int, std::string>>());
    std::vector<int> indegree(26, 0);
    std::vector<int> outdegree(26, 0);

    for (auto &word : words) {
      int u = word.front() - 'a';
      int v = word.back() - 'a';

      adj[u].emplace_back(v, word);
      ++indegree[v];
      ++outdegree[u];
    }

    bool impossible = false;

    int start = -1;
    int start_count = 0;
    int end_count = 0;

    for (int i = 0; i < 26; ++i) {
      if (indegree[i] + 1 == outdegree[i]) {
        start = i;
        ++start_count;
      } else if (outdegree[i] + 1 == indegree[i]) {
        ++end_count;
      } else if (outdegree[i] != indegree[i]) {
        impossible = true;
        break;
      }
    }

    if (impossible || !((start_count == 0 && end_count == 0) ||
                        (start_count == 1 && end_count == 1))) {
      std::cout << "***\n";
      continue;
    }

    if (start == -1) {
      start = words.back().front() - 'a';
    }

    std::vector<std::string> res;
    auto dfs = [&](auto &&self, int u) -> void {
      while (!adj[u].empty()) {
        auto [v, word] = adj[u].back();
        adj[u].pop_back();

        self(self, v);
        res.emplace_back(word);
      }
    };

    dfs(dfs, start);

    if (res.size() != n) {
      std::cout << "***\n";
      continue;
    } else {
      std::reverse(res.begin(), res.end());
      std::cout << res.front();
      for (int i = 1; i < n; ++i) {
        std::cout << '.' << res[i];
      }
      std::cout << '\n';
    }
  }
}