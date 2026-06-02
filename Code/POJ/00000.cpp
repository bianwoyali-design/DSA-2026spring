#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::ranges::copy(std::views::iota(1, 3000001),
                    std::ostream_iterator<int>(std::cout, "\n"));
}