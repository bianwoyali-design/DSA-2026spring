#include <iostream>
#include <queue>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n{};
  std::cin >> n;
  std::priority_queue<int, std::vector<int>, std::greater<>> pq;
  while (n--) {
    int num;
    std::cin >> num;
    pq.emplace(num);
  }

  int total_wpl = 0;
  while (pq.size() > 1) {
    int first = pq.top();
    pq.pop();
    int second = pq.top();
    pq.pop();
    int sum = first + second;
    total_wpl += sum;
    pq.emplace(sum);
  }

  std::cout << total_wpl << '\n';
}