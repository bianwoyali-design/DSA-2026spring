#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n = 0;
  std::cin >> n;
  std::vector<int> arr(n, 0);
  for (auto &&a : arr) {
    std::cin >> a;
  }
  int sum = 0;
  std::cin >> sum;

  std::sort(arr.begin(), arr.end());

  for (int l = 0, r = arr.size() - 1; l < r;) {
    int curr_sum = arr[l] + arr[r];
    if (curr_sum > sum) {
      --r;
    } else if (curr_sum < sum) {
      ++l;
    } else {
      std::cout << arr[l] << ' ' << arr[r] << '\n';
      return 0;
    }
  }

  std::cout << "No\n";
  return 0;
}