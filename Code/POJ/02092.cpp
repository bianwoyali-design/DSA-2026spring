#include <iostream>
#include <map>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int N, M;
  while (std::cin >> N >> M && M != 0 && N != 0) {
    std::map<int, int> status;
    for (int i = 0; i < M; ++i)
      for (int j = 0; j < N; ++j) {
        int id;
        std::cin >> id;
        ++status[id];
      }

    int max_score = 0;
    for (const auto &m : status)
      max_score = std::max(max_score, m.second);

    int second_score = 0;
    for (const auto &m : status)
      if (m.second > second_score && m.second < max_score)
        second_score = m.second;

    for (const auto &m : status)
      if (m.second == second_score)
        std::cout << m.first << ' ';
    std::cout << '\n';
  }
}