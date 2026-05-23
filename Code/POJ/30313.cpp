#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <tuple>
#include <vector>

class DSU {
private:
  std::vector<int> parent;
  std::vector<int> rank;

public:
  explicit DSU(int n) : parent(n), rank(n, 0) {
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }

  auto Find(int x) -> int {
    if (parent[x] == x) {
      return x;
    }
    return parent[x] = Find(parent[x]);
  }

  auto Union(int x, int y) -> bool {
    int root_x = Find(x);
    int root_y = Find(y);
    if (root_x == root_y) {
      return false;
    }

    if (rank[root_x] < rank[root_y]) {
      parent[root_x] = root_y;
    } else if (rank[root_x] > rank[root_y]) {
      parent[root_y] = root_x;
    } else {
      parent[root_x] = root_y;
      ++rank[root_y];
    }
    return true;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;
  std::vector<std::tuple<int, int, int>> edge;
  edge.reserve(m);
  std::vector neighbor(n, std::vector<int>());
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    --u, --v;
    edge.emplace_back(w, u, v);
    neighbor[u].emplace_back(v);
    neighbor[v].emplace_back(u);
  }

  int comp_count = 0;
  std::vector comp(n, -1);
  std::list<int> unvisited;
  for (int i = 0; i < n; ++i) {
    unvisited.emplace_back(i);
  }
  std::vector<int> marked(n, 0);
  int stamp = 0;

  while (!unvisited.empty()) {
    int start = unvisited.front();
    unvisited.pop_front();
    comp[start] = comp_count;

    std::queue<int> q;
    q.emplace(start);

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      ++stamp;
      for (int v : neighbor[u]) {
        marked[v] = stamp;
      }

      for (auto it = unvisited.begin(); it != unvisited.end();) {
        int v = *it;

        if (marked[v] != stamp) {
          comp[v] = comp_count;
          q.emplace(v);
          it = unvisited.erase(it);
        } else {
          ++it;
        }
      }
    }

    ++comp_count;
  }

  std::sort(edge.begin(), edge.end());
  long long mst_weight = 0;
  int count = 0;
  DSU dsu(comp_count);
  for (auto &&[w, u, v] : edge) {
    if (count == comp_count - 1) {
      break;
    }

    int cu = comp[u];
    int cv = comp[v];
    if (cu != cv && dsu.Union(cu, cv)) {
      mst_weight += w;
      ++count;
    }
  }

  std::cout << mst_weight << '\n';
}
