#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;
  std::vector reachable(n, std::vector<int>(n, false));
  for (int i = 0; i < m; ++i) {
    int u, v, status;
    std::cin >> u >> v >> status;
    if (status == 1) {
      reachable[u][v] = true;
    } else {
      reachable[v][u] = true;
    }
  }

  for (int i = 0; i < n; ++i) {
    reachable[i][i] = true;
  }

  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        reachable[i][j] =
            reachable[i][j] || (reachable[i][k] && reachable[k][j]);
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    int determined = 0;

    for (int j = 0; j < n; ++j) {
      if (i == j) {
        continue;
      }

      if (reachable[i][j] || reachable[j][i]) {
        ++determined;
      }
    }

    if (determined == n - 1) {
      ++ans;
    }
  }

  std::cout << ans << '\n';
}