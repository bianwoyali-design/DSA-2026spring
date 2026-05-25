#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n{}, m{};
  std::cin >> n >> m;

  std::vector<int> weight(n, 0);
  std::vector<int> value(n, 0);
  for (int i = 0; i < n; ++i) {
    std::cin >> weight[i];
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> value[i];
  }

  std::vector adj(n, std::vector<int>());
  for (int i = 0; i < n; ++i) {
    int d;
    std::cin >> d;
    --d;
    if (d != -1) {
      adj[i].emplace_back(d);
    }
  }

  int comp_count = 1;
  std::vector<int> comp(n, 0);
  auto tarjan = [&]() -> void {
    int timer = 0;
    std::vector<int> dfn(n, -1);
    std::vector<int> low(n, -1);
    std::vector<int> stack;
    std::vector<bool> on_stack(n, false);

    auto dfs = [&](this auto &&self, int u) -> void {
      dfn[u] = low[u] = timer++;
      stack.emplace_back(u);
      on_stack[u] = true;

      for (int v : adj[u]) {
        if (dfn[v] == -1) {
          self(v);
          low[u] = std::min(low[u], low[v]);
        } else if (on_stack[v]) {
          low[u] = std::min(low[u], dfn[v]);
        }
      }

      if (dfn[u] == low[u]) {
        while (true) {
          int x = stack.back();
          stack.pop_back();
          on_stack[x] = false;
          comp[x] = comp_count;
          if (x == u) {
            break;
          }
        }
        ++comp_count;
      }
    };

    for (int i = 0; i < n; ++i) {
      if (dfn[i] == -1) {
        dfs(i);
      }
    }
  };

  tarjan();

  std::vector dag(comp_count, std::vector<int>());
  std::vector<int> indegree(comp_count, 0);
  std::vector<int> comp_weight(comp_count, 0);
  std::vector<int> comp_value(comp_count, 0);

  for (int u = 0; u < n; ++u) {
    comp_weight[comp[u]] += weight[u];
    comp_value[comp[u]] += value[u];

    for (int v : adj[u]) {
      int cu = comp[u], cv = comp[v];
      if (cu == cv) {
        continue;
      }
      dag[cv].emplace_back(cu);
    }
  }

  for (int i = 1; i < comp_count; ++i) {
    std::ranges::sort(dag[i]);
    dag[i].erase(std::ranges::unique(dag[i]).begin(), dag[i].end());
    for (int v : dag[i]) {
      ++indegree[v];
    }
  }

  for (int i = 1; i < comp_count; ++i) {
    if (indegree[i] == 0) {
      dag[0].emplace_back(i);
    }
  }

  std::vector dp(comp_count, std::vector<int>(m + 1, 0));

  auto dfs = [&](this auto &&dfs, int u) -> void {
    if (comp_weight[u] <= m) {
      for (int j = comp_weight[u]; j <= m; ++j) {
        dp[u][j] = comp_value[u];
      }
    }

    for (int v : dag[u]) {
      dfs(v);
      for (int j = m; j >= comp_weight[u]; --j) {
        for (int k = 0; k <= j - comp_weight[u]; ++k) {
          dp[u][j] = std::max(dp[u][j], dp[u][j - k] + dp[v][k]);
        }
      }
    }
  };

  dfs(0);

  std::cout << dp[0][m] << '\n';
}
