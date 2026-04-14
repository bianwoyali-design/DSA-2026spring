#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  std::cin >> t;

  while (t--) {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> g(n);

    for (int i = 0; i < n - 1; ++i) {
      int u, v;
      std::cin >> u >> v;
      --u, --v;
      g[v].emplace_back(u);
      g[u].emplace_back(v);
    }

    std::vector<long long> leaves(n, 0);
    auto dfs = [&](this auto &&dfs, int root, int prev) -> void {
      if (g[root].size() == 1 && g[root][0] == prev) {
        leaves[root] = 1;
        return;
      }

      for (const auto v : g[root]) {
        if (v != prev) {
          dfs(v, root);
          leaves[root] += leaves[v];
        }
      }
    };

    dfs(0, -1);

    int q;
    std::cin >> q;
    while (q--) {
      int x, y;
      std::cin >> x >> y;
      --x, --y;
      std::cout << leaves[x] * leaves[y] << '\n';
    }
  }
}