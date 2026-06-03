#include <iomanip>
#include <ios>
#include <iostream>
#include <map>
#include <string>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int total = 0;
  std::string str;
  std::map<std::string, int> dict;
  while (std::getline(std::cin, str)) {
    ++dict[str];
    ++total;
  }

  for (const auto& [name, count] : dict) {
    double rate = static_cast<double>(count) / total * 100.0;
    std::cout << name << ' ' << std::fixed << std::setprecision(4) << rate << '\n';
  }
}