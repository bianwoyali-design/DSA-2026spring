#include <iostream>
#include <string>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n{};
  std::cin >> n;

  std::vector data(13, std::vector(32, std::vector<std::string>()));
  while (n--) {
    std::string id;
    int month, day;
    std::cin >> id >> month >> day;
    data[month][day].emplace_back(id);
  }

  for (int i = 1; i <= 12; ++i) {
    for (int j = 1; j <= 31; ++j) {
      if (data[i][j].size() > 1) {
        std::cout << i << ' ' << j;
        for (const auto& id : data[i][j]) {
          std::cout << ' ' << id;
        }
        std::cout << '\n';
      }
    }
  }
}
