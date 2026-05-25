#include <iostream>
#include <queue>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;
  std::vector adj(n + 1, std::vector<int>());
  std::vector<int> indegree(n + 1, 0);
  for (int i = 0; i < m; ++i) {
    int a, b;
    char op;
    std::cin >> a >> op >> b;
    adj[a].emplace_back(b);
    ++indegree[b];
  }

  std::queue<int> q;
  for (int i = 1; i <= n; ++i) {
    if (!indegree[i]) {
      q.emplace(i);
    }
  }

  bool determined = true;
  std::vector<int> order;
  while (!q.empty()) {
    if (q.size() > 1) {
      determined = false;
    }

    int u = q.front();
    q.pop();
    order.emplace_back(u);

    for (int v : adj[u]) {
      --indegree[v];
      if (!indegree[v]) {
        q.emplace(v);
      }
    }
  }

  if (order.size() != n) {
    std::cout << "Device error.\n";
    return 0;
  }

  if (!determined) {
    std::cout << "Not determined.\n";
    return 0;
  }

  int ptr = 0;
  std::vector<int> tree(n + 1, 0);
  auto dfs = [&](auto &&self, int u) -> void {
    if (u > n) {
      return;
    }
    tree[u] = order[ptr++];
    self(self, u << 1 | 1);
    self(self, u << 1);
  };

  dfs(dfs, 1);

  std::vector<int> res;
  auto inorder = [&](auto &&self, int i) -> void {
    if (i > n) {
      return;
    }
    self(self, i << 1);
    res.emplace_back(tree[i]);
    self(self, i << 1 | 1);
  };

  inorder(inorder, 1);

  for (int i = 0; i < n; ++i) {
    std::cout << res[i] << " \n"[i + 1 == n];
  }
}