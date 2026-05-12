#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n{};
  std::cin >> n;
  std::vector<int> costs(n, 0);
  for (auto &c : costs) {
    std::cin >> c;
  }

  int m{};
  std::cin >> m;
  std::vector g(n, std::vector<int>());
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    g[--u].emplace_back(--v);
  }

  constexpr int MOD = 1000000007;
  long long min_total_cost = 0;
  long long min_comb = 1;
  auto scc_condensation = [&]() -> void {
    int timer = 0;
    std::vector<int> dfn(n, -1);
    std::vector<int> low(n, -1);
    std::vector<int> stack;
    std::vector<bool> on_stack(n, false);

    auto dfs = [&](this auto &&self, int u) -> void {
      dfn[u] = low[u] = timer++;
      stack.emplace_back(u);
      on_stack[u] = true;

      for (auto v : g[u]) {
        if (dfn[v] == -1) {
          self(v);
          low[u] = std::min(low[u], low[v]);
        } else if (on_stack[v]) {
          low[u] = std::min(low[u], dfn[v]);
        }
      }

      if (dfn[u] == low[u]) {
        int min_cost = INT_MAX;
        int min_count = 0;
        while (true) {
          int node = stack.back();
          stack.pop_back();
          on_stack[node] = false;
          if (min_cost > costs[node]) {
            min_cost = costs[node];
            min_count = 1;
          } else if (min_cost == costs[node]) {
            ++min_count;
          }
          if (node == u) {
            break;
          }
        }
        min_total_cost += min_cost;
        min_comb = min_comb * min_count % MOD;
      }
    };

    for (int i = 0; i < n; ++i) {
      if (dfn[i] == -1) {
        dfs(i);
      }
    }
  };

  scc_condensation();
  std::cout << min_total_cost << ' ' << min_comb << '\n';
}
