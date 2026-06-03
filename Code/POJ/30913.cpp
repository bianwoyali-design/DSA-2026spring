#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;

  std::vector g(n, std::vector<std::pair<int, int>>());

  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    --u, --v;
    g[u].emplace_back(v, w);
  }

  int src;
  std::cin >> src;
  --src;

  int timer = 0;
  int component_count = 0;
  std::vector<int> dfn(n, -1);
  std::vector<int> low(n, -1);
  std::vector<int> stack{};
  std::vector<bool> on_stack(n, false);
  std::vector<int> comp(n, -1);

  auto dfs = [&](auto &&self, int u) -> void {
    dfn[u] = low[u] = ++timer;
    stack.emplace_back(u);
    on_stack[u] = true;

    for (auto [v, _] : g[u]) {
      if (dfn[v] == -1) {
        self(self, v);
        low[u] = std::min(low[u], low[v]);
      } else if (on_stack[v]) {
        low[u] = std::min(low[u], dfn[v]);
      }
    }

    if (low[u] == dfn[u]) {
      while (true) {
        int x = stack.back();
        stack.pop_back();
        on_stack[x] = false;
        comp[x] = component_count;
        if (x == u) {
          break;
        }
      }
      ++component_count;
    }
  };

  for (int i = 0; i < n; ++i) {
    if (dfn[i] == -1) {
      dfs(dfs, i);
    }
  }

  std::vector dag(component_count, std::vector<std::pair<int, long long>>());
  std::vector<int> indegree(component_count, 0);
  std::vector<long long> value(component_count, 0);

  auto collect = [&](int w) -> long long {
    long long k = std::ceil((std::sqrt(8 * w + 1) - 1) / 2.0) + 1;
    long long t = k - 1;
    return t * w - (t - 1) * t * (t + 1) / 6;
  };

  for (int u = 0; u < n; ++u) {
    for (auto [v, w] : g[u]) {
      int cu = comp[u], cv = comp[v];
      if (cu == cv) {
        value[cu] += collect(w);
        continue;
      }
      dag[cu].emplace_back(cv, w);
    }
  }

  for (int u = 0; u < component_count; ++u) {
    for (auto [v, _] : dag[u]) {
      ++indegree[v];
    }
  }

  std::queue<int> q;
  std::vector<int> topo;
  for (int i = 0; i < component_count; ++i) {
    if (!indegree[i]) {
      q.emplace(i);
    }
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    topo.emplace_back(u);

    for (auto [v, _] : dag[u]) {
      --indegree[v];
      if (!indegree[v]) {
        q.emplace(v);
      }
    }
  }

  std::vector<long long> dp(component_count, 0);
  for (int i = 0; i < component_count; ++i) {
    dp[i] = value[i];
  }
  for (int i = topo.size() - 1; i >= 0; --i) {
    int u = topo[i];
    long long best = 0;
    for (auto [v, w] : dag[u]) {
      best = std::max(best, dp[v] + w);
    }
    dp[u] += best;
  }

  std::cout << dp[comp[src]] << '\n';
}