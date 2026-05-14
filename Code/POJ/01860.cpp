#include <iostream>
#include <vector>

struct Node {
  int a;
  int b;
  double rab;
  double cab;
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int N{}, M{}, S{};
  double V{};
  std::cin >> N >> M >> S >> V;

  std::vector<Node> edge;
  for (int i = 0; i < M; ++i) {
    int A, B;
    double R_ab, C_ab, R_ba, C_ba;
    std::cin >> A >> B >> R_ab >> C_ab >> R_ba >> C_ba;
    edge.emplace_back(Node{A, B, R_ab, C_ab});
    edge.emplace_back(Node{B, A, R_ba, C_ba});
  }

  std::vector<double> dp(N + 1, 0);
  dp[S] = V;

  for (int i = 0; i < N; ++i) {
    bool flag = false;
    for (auto &[u, v, rate, change] : edge) {
      if (dp[v] < (dp[u] - change) * rate) {
        dp[v] = (dp[u] - change) * rate;
        flag = true;
        if (v == S && dp[v] > V) {
          std::cout << "YES\n";
          return 0;
        }
      }
    }
    if (i == N - 1 && flag) {
      std::cout << "YES\n";
      return 0;
    }

    if (!flag) {
      break;
    }
  }

  std::cout << "NO\n";
}