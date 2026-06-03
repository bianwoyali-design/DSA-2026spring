#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

class MedianCost {
private:
  std::priority_queue<long long> low;
  std::priority_queue<long long, std::vector<long long>, std::greater<>> high;
  long long sum_low = 0;
  long long sum_high = 0;

  void balance() {
    while (low.size() < high.size()) {
      long long x = high.top();
      high.pop();
      sum_high -= x;
      low.push(x);
      sum_low += x;
    }

    while (low.size() > high.size() + 1) {
      long long x = low.top();
      low.pop();
      sum_low -= x;
      high.push(x);
      sum_high += x;
    }
  }

public:
  void insert(long long x) {
    if (low.empty() || x <= low.top()) {
      low.push(x);
      sum_low += x;
    } else {
      high.push(x);
      sum_high += x;
    }

    balance();
  }

  auto cost() -> long long {
    if (low.empty()) {
      return 0;
    }

    long long median = low.top();
    return median * static_cast<long long>(low.size()) - sum_low + sum_high -
           median * static_cast<long long>(high.size());
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;

  std::vector<long long> x(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> x[i];
  }

  std::vector<long long> prefix(n + 1, 0);
  std::vector<long long> suffix(n + 2, 0);

  MedianCost left;
  for (int i = 1; i <= n; ++i) {
    left.insert(x[i]);
    prefix[i] = left.cost();
  }

  MedianCost right;
  for (int i = n; i >= 1; --i) {
    right.insert(x[i]);
    suffix[i] = right.cost();
  }

  long long answer = prefix[n];

  for (int t = 0; t <= n; ++t) {
    answer = std::min(answer, prefix[t] + suffix[t + 1]);
  }

  std::cout << answer * 2 << '\n';
}