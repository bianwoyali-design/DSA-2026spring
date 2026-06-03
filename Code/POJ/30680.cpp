#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::unordered_map<int, std::vector<int>> tree;
  std::map<int, int> indegree;
  while (n--) {
    std::string str;
    std::getline(std::cin, str);

    bool first = true;
    int root;
    std::stringstream ss(str);
    for (int node; ss >> node;) {
      if (first) {
        root = node;
        if (!indegree[root])
          indegree[root] = 0;
        first = false;
      } else {
        tree[root].emplace_back(node);
        ++indegree[node];
      }
    }
  }

  std::vector<int> root;
  for (auto [node, d] : indegree) {
    if (!d) {
      root.emplace_back(node);
    }
  }

  auto dfs = [&](auto &&self, int root) -> void {
    if (tree[root].empty()) {
      std::cout << root << '\n';
      return;
    }

    std::vector<int> c;
    c.emplace_back(root);
    for (auto child : tree[root]) {
      c.emplace_back(child);
    }

    std::sort(c.begin(), c.end());

    for (auto node : c) {
      if (node == root) {
        std::cout << node << '\n';
      } else {
        self(self, node);
      }
    }
  };

  for (auto node : root) {
    dfs(dfs, node);
  }
}
