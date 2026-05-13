#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n{};
  std::cin >> n;
  std::vector<int> distance(n, 0);
  std::vector<int> price(n, 0);
  std::vector<double> rating(n, 0);
  std::vector<std::pair<int, double>> house(n);

  for (int i = 0; i < n; ++i) {
    char left, comma, right;
    int x, y;
    std::cin >> left >> x >> comma >> y >> right;
    distance[i] = x + y;
  }

  for (int i = 0; i < n; ++i) {
    std::cin >> price[i];
    rating[i] = static_cast<double>(distance[i]) / static_cast<double>(price[i]);
    house[i].first = price[i];
    house[i].second = rating[i];
  }

  std::sort(rating.begin(), rating.end());
  std::sort(price.begin(), price.end());
  double mid_rating =
      n % 2 == 0 ? (rating[n / 2] + rating[n / 2 - 1]) / 2.0 : rating[n / 2];
  double mid_price =
      n % 2 == 0 ? (price[n / 2] + price[n / 2 - 1]) / 2.0 : price[n / 2];

  int count = 0;
  for (int i = 0; i < n; ++i) {
    if (house[i].first < mid_price && house[i].second > mid_rating) {
      ++count;
    }
  }
  std::cout << count << '\n';
}
