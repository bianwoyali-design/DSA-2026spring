#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Tree {
private:
  int n;
  int root;
  std::vector<std::vector<int>> adj;
  std::vector<int> val;

public:
  Tree(int n) : n(n), adj(n) {}

  auto buildAdj() noexcept -> void {
    std::vector<std::vector<int>> ipt(n);
    for (auto &row : ipt) {
      std::string s;
      std::getline(std::cin, s);
      std::stringstream ss(s);
      int v;
      while (ss >> v) {
        val.emplace_back(v);
        row.emplace_back(v);
      }
    }

    std::sort(val.begin(), val.end());
    val.erase(std::unique(val.begin(), val.end()), val.end());

    for (auto &row : ipt)
      for (auto &x : row)
        x = static_cast<int>(std::lower_bound(val.begin(), val.end(), x) -
                             val.begin());

    adj.assign(static_cast<int>(val.size()), {});
    std::vector<bool> has_parent(val.size(), false);

    for (const auto &row : ipt) {
      int parent = row.front();
      for (int i = 1; i < static_cast<int>(row.size()); ++i) {
        adj[parent].emplace_back(row[i]);
        has_parent[row[i]] = true;
      }
    }

    root = static_cast<int>(
        std::find(has_parent.begin(), has_parent.end(), false) -
        has_parent.begin());
  }

  auto dfs(int node) noexcept -> void {
    std::sort(adj[node].begin(), adj[node].end());

    int i = 0;
    for (; i < static_cast<int>(adj[node].size()) && adj[node][i] < node; ++i)
      dfs(adj[node][i]);
    std::cout << val[node] << '\n';
    for (; i < static_cast<int>(adj[node].size()); ++i)
      dfs(adj[node][i]);
  }

  auto solve() noexcept -> void { dfs(root); }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;
  std::cin.ignore();

  Tree tree(n);
  tree.buildAdj();
  tree.solve();
}