#include <deque>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;

  std::vector<int> team(n, 0);
  std::vector<char> p(n);

  int count = 1;
  std::deque<int> qt, qd, qh;

  for (int i = 0; i < n; ++i) {
    std::cin >> p[i];
  }

  for (int i = 0; i < n; ++i) {
    if (p[i] == 'D') {
      qd.emplace_back(i);
    }
    if (p[i] == 'H') {
      qh.emplace_back(i);
    }
    if (p[i] == 'T') {
      qt.emplace_back(i);
    }

    if (qt.size() >= 1 && qd.size() >= 3 && qh.size() >= 1) {
      team[qt.front()] = count;
      qt.pop_front();
      team[qh.front()] = count;
      qh.pop_front();
      for (int x = 0; x < 3; ++x) {
        team[qd.front()] = count;
        qd.pop_front();
      }
      ++count;
    }
  }

  for (int i = 0; i < n; ++i) {
    std::cout << team[i] << ' ';
  }
}