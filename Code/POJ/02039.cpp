#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int col;
  std::cin >> col;
  std::string s;
  std::cin >> s;

  std::vector<std::vector<char>> matrix;
  std::vector<char> row;
  for (const auto c : s) {
    row.emplace_back(c);
    if (row.size() == col) {
      if (matrix.size() % 2 == 0) {
        matrix.emplace_back(std::move(row));
      } else {
        std::reverse(row.begin(), row.end());
        matrix.emplace_back(std::move(row));
      }
    }
  }

  for (int i = 0; i < col; ++i)
    for (auto &j : matrix)
      std::cout << j[i];
}