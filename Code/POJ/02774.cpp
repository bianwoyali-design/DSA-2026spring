#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int N, K;
  std::cin >> N >> K;
  std::vector<int> length(N);
  for (auto &l : length)
    std::cin >> l;

  auto check = [&](int len) -> bool {
    int num = 0;
    for (const auto &l : length)
      num += (l / len);
    return num >= K;
  };

  int l = 1, r = *std::max_element(length.begin(), length.end());
  int ans = 0;
  while (l <= r) {
    int mid = l + ((r - l) >> 1);
    if (check(mid)) {
      ans = mid;
      l = mid + 1;
    } else
      r = mid - 1;
  }

  std::cout << ans << '\n';
}