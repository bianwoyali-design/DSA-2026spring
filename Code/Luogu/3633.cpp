#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

class Solution {
public:
  auto earliestFinishTime(const std::vector<int> &landStartTime,
                          const std::vector<int> &landDuration,
                          const std::vector<int> &waterStartTime,
                          const std::vector<int> &waterDuration) -> int {
    auto landIndices = std::views::iota(std::size_t{0}, landStartTime.size());
    int land = std::ranges::min(landIndices |
                                std::views::transform([&](std::size_t i) {
                                  return landStartTime[i] + landDuration[i];
                                }));
    auto waterIndices = std::views::iota(std::size_t{0}, waterStartTime.size());
    int waterAfterLand = std::ranges::min(
        waterIndices | std::views::transform([&](std::size_t i) {
          return std::max(land, waterStartTime[i]) + waterDuration[i];
        }));

    int water = std::ranges::min(waterIndices |
                                 std::views::transform([&](std::size_t i) {
                                   return waterStartTime[i] + waterDuration[i];
                                 }));
    int landAfterWater = std::ranges::min(
        landIndices | std::views::transform([&](std::size_t i) {
          return std::max(water, landStartTime[i]) + landDuration[i];
        }));

    return std::min(waterAfterLand, landAfterWater);
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::vector<int> landStartTime = {2, 8}, landDuration = {4, 1},
                   waterStartTime = {6}, waterDuration = {3};
  Solution sol;
  std::cout << sol.earliestFinishTime(landStartTime, landDuration,
                                      waterStartTime, waterDuration)
            << '\n';
}
