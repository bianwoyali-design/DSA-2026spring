#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
public:
  auto criticalConnections(int n, std::vector<std::vector<int>> &connections)
      -> std::vector<std::vector<int>> {
    std::vector adj(n, std::vector<Edge>());
    for (int id = 0; id < static_cast<int>(connections.size()); ++id) {
      int u = connections[id][0];
      int v = connections[id][1];
      adj[u].push_back({v, id});
      adj[v].push_back({u, id});
    }

    return tarjan(adj);
  }

private:
  struct Edge {
    int to;
    int id;
  };

  auto tarjan(const std::vector<std::vector<Edge>> &adj)
      -> std::vector<std::vector<int>> {
    int n = adj.size();
    int timer = 0;
    std::vector<int> dfn(n, -1);
    std::vector<int> low(n, -1);
    std::vector<std::vector<int>> bridges;

    auto dfs = [&](this auto &&self, int u, int parent_edge) -> void {
      dfn[u] = low[u] = timer++;

      for (auto [v, edge_id] : adj[u]) {
        if (edge_id == parent_edge) {
          continue;
        }
        if (dfn[v] == -1) {
          self(v, edge_id);
          low[u] = std::min(low[u], low[v]);
          if (low[v] > dfn[u]) {
            std::vector<int> edge = {u, v};
            bridges.emplace_back(edge);
          }
        } else {
          low[u] = std::min(low[u], dfn[v]);
        }
      }
    };

    for (int u = 0; u < n; ++u) {
      if (dfn[u] == -1) {
        dfs(u, -1);
      }
    }

    return bridges;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n = 4;
  std::vector<std::vector<int>> connections = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};
  Solution sol;
  auto ans = sol.criticalConnections(n, connections);
  for (auto row : ans) {
    std::cout << row[0] << ' ' << row[1] << '\n';
  }
}
